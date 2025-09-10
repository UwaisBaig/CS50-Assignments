import requests
from flask import Flask, render_template, request, redirect, url_for, session, flash
from cs50 import SQL
import re
from werkzeug.security import generate_password_hash, check_password_hash
from functools import wraps

# --------------------------
# Configure app
# --------------------------
app = Flask(__name__)
app.secret_key = "your_secret_key"  # required for sessions

# Regex for valid domain or URL
URL_REGEX = re.compile(
    r'^(https?:\/\/)?'                         # optional http/https
    r'([a-zA-Z0-9-]+\.)+[a-zA-Z]{2,}'          # domain name
    r'(\/.*)?$'                                # optional path
)

# Single Database (users + sites + todos)
db = SQL("sqlite:///blocked_sites.db")

# --------------------------
# Helpers
# --------------------------
def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


@app.before_request
def require_login():
    # Allow these routes without login
    allowed_routes = {"login", "register", "static"}

    # If no user logged in and route is not in allowed ones → redirect
    if "user_id" not in session and request.endpoint not in allowed_routes:
        return redirect("/login")


# --------------------------
# Home
# --------------------------
@app.route("/")
def index():
    return render_template("home.html")


# --------------------------
# Auth
# --------------------------
@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username").strip()
        password = request.form.get("password")

        if not username or not password:
            flash("Must provide username and password", "danger")
            return redirect("/register")

        hash_pw = generate_password_hash(password)

        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash_pw)
        except Exception:
            flash("Username already exists. Please choose another.", "warning")
            return redirect("/register")

        flash("Registration successful! Please log in.", "success")
        return redirect("/login")

    return render_template("register.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    session.clear()
    if request.method == "POST":
        username = request.form.get("username").strip()
        password = request.form.get("password")

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], password):
            flash("Invalid username or password", "danger")
            return redirect("/login")

        session["user_id"] = rows[0]["id"]
        flash("Welcome back!", "success")
        return redirect("/")
    return render_template("login.html")


@app.route("/logout", methods=["GET"])
def logout():
    session.clear()
    return redirect("/")


@app.route("/delete_account", methods=["POST"])
@login_required
def delete_account():
    user_id = session["user_id"]

    try:
        # Delete user's todos
        db.execute("DELETE FROM todos WHERE user_id = ?", user_id)

        # Delete user's blocked sites
        db.execute("DELETE FROM sites WHERE user_id = ?", user_id)

        # Delete the user account itself
        db.execute("DELETE FROM users WHERE id = ?", user_id)

        # Clear session
        session.clear()

    except Exception as e:
        return f"Error deleting account: {str(e)}", 500

    return redirect("/register")  # or "/" with a flash message



# --------------------------
# To-Do Feature
# --------------------------
@app.route("/todo", methods=["GET", "POST"])
@login_required
def todo():
    if request.method == "POST":
        task = request.form.get("task", "").strip()

        if not task or len(task) < 3:
            flash("Please enter a valid task (at least 3 characters).", "danger")
        else:
            # Check duplicates
            existing = db.execute(
                "SELECT * FROM todos WHERE task = ? AND user_id = ?",
                task, session["user_id"]
            )
            if existing:
                flash("Task already exists in your list.", "warning")
            else:
                try:
                    db.execute(
                        "INSERT INTO todos (task, user_id) VALUES (?, ?)",
                        task, session["user_id"]
                    )
                    flash("Task added successfully!", "success")
                except Exception as e:
                    flash(f"Error adding task: {str(e)}", "danger")

    tasks = db.execute(
        "SELECT * FROM todos WHERE user_id = ? ORDER BY added_at DESC",
        session["user_id"]
    )
    total = len(tasks)
    completed = sum(1 for t in tasks if t["completed"] == 1)
    progress = int((completed / total) * 100) if total > 0 else 0

    return render_template("todo.html", todos=tasks, progress=progress)

@app.route("/todo/undo/<int:task_id>", methods=["POST"])
@login_required
def undo_task(task_id):
    try:
        db.execute("UPDATE todos SET completed = 0 WHERE id = ? AND user_id = ?", task_id, session["user_id"])
    except Exception as e:
        return f"Error undoing task: {str(e)}"
    return redirect(url_for("todo"))


@app.route("/todo/delete/<int:task_id>", methods=["POST"])
@login_required
def delete_task(task_id):
    db.execute("DELETE FROM todos WHERE id = ? AND user_id = ?", task_id, session["user_id"])
    return redirect("/todo")


@app.route("/todo/complete/<int:task_id>", methods=["POST"])
@login_required
def complete_task(task_id):
    db.execute("UPDATE todos SET completed = 1 WHERE id = ? AND user_id = ?", task_id, session["user_id"])
    return redirect("/todo")


# --------------------------
# Motivational Quotes (API)
# --------------------------
@app.route("/quotes")
@login_required
def quotes():
    try:
        res = requests.get("https://zenquotes.io/api/random", timeout=5)
        res.raise_for_status()
        data = res.json()
        quote_text = data[0]['q']
        author = data[0]['a']
    except requests.exceptions.Timeout:
        quote_text = "The request timed out. Please try again later."
        author = ""
    except requests.exceptions.RequestException:
        quote_text = "Could not fetch quote. Please check your connection."
        author = ""
    except Exception:
        quote_text = "Something went wrong. Please try again later."
        author = ""

    return render_template("quotes.html", quote=quote_text, author=author)


# --------------------------
# Site Blocker
# --------------------------
@app.route("/blocker", methods=["GET", "POST"])
@login_required
def blocker():
    user_id = session["user_id"]

    if request.method == "POST":
        site = request.form.get("site", "").strip().lower()

        # Normalize URL (remove protocols and trailing slashes)
        site = site.replace("https://", "").replace("http://", "").strip("/")

        # Empty check
        if not site:
            flash("⚠️ Please enter a site before adding.", "warning")
            return redirect("/blocker")

        # Validate basic domain format
        if not URL_REGEX.match(site):
            flash("❌ Invalid website address. Try like 'example.com'", "danger")
            return redirect("/blocker")

        # Duplicate check
        existing = db.execute(
            "SELECT * FROM sites WHERE url = ? AND user_id = ?", site, user_id
        )
        if existing:
            flash("ℹ️ This site is already blocked.", "info")
            return redirect("/blocker")

        # Insert site
        try:
            db.execute("INSERT INTO sites (url, user_id) VALUES (?, ?)", site, user_id)
            flash(f"✅ {site} has been blocked!", "success")
        except Exception as e:
            flash(f"❌ Error adding site: {e}", "danger")

        return redirect("/blocker")

    # GET request → show blocked sites
    blocked_sites = db.execute(
        "SELECT * FROM sites WHERE user_id = ? ORDER BY added_at DESC", user_id
    )
    return render_template("blocker.html", blocked_sites=blocked_sites)


@app.route("/remove_site", methods=["POST"])
@login_required
def remove_site():
    site_id = request.form.get("site_id")

    if not site_id:
        flash("⚠️ Invalid request. No site selected.", "warning")
        return redirect("/blocker")

    # Delete only if belongs to current user
    rows_deleted = db.execute(
        "DELETE FROM sites WHERE id = ? AND user_id = ?", site_id, session["user_id"]
    )

    if rows_deleted:
        flash("🗑️ Site removed successfully.", "success")
    else:
        flash("❌ Could not remove site (not found or unauthorized).", "danger")

    return redirect("/blocker")

# --------------------------
# Run
# --------------------------
if __name__ == "__main__":
    app.run(debug=True)
