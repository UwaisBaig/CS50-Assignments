# AzmFlow
#### Video Demo: https://youtu.be/GaJzepYHO9M
#### Description:

## Introduction
AzmFlow is a productivity web application created as my final project for CS50x. The name is inspired by the Urdu word *Azm*, meaning “determination,” and the English word *Flow*, symbolizing focus and discipline. Combined, **AzmFlow** represents a tool designed to help individuals stay productive, motivated, and organized in an increasingly distracting digital world.

The project has three major features—**a To-Do List**, **Motivational Quotes**, and a **Site Blocker (Demo)**—all integrated within a secure user authentication system. Together, these features form a holistic productivity solution that balances organization, inspiration, and focus.

---

## Features

### 1. Secure User Authentication
AzmFlow begins with a simple but secure login and registration system. Users must create an account with a unique username and password, which is hashed before storage using Werkzeug’s security utilities. This ensures that no sensitive information is ever stored in plain text.

- **Register**: Create a new account with username and password.
- **Login**: Log into an existing account and access personal data.
- **Logout**: Securely end the session.

This design guarantees that each user’s tasks, blocked sites, and preferences remain private and personalized.

---

### 2. To-Do List
The To-Do List is the core productivity tool in AzmFlow. Users can:

- Add new tasks through a simple input form.
- View all pending tasks in a clean, card-based list.
- Remove or mark tasks as complete when finished.

Tasks are stored in the SQLite database, which means they persist even if the user logs out or refreshes the page. Validation ensures that users cannot submit empty tasks or duplicates, and all error messages are presented using friendly Bootstrap alerts.

The design emphasizes clarity and accountability. By breaking down work into small, achievable goals, users can better manage their time and track progress.

---

### 3. Motivational Quotes
Staying disciplined is easier when paired with inspiration. AzmFlow integrates a **Motivational Quotes feature**, which fetches quotes from a public API and displays them on the user’s dashboard.

- Each quote is shown in a styled card.
- Refreshing or revisiting the page fetches new quotes.
- Quotes provide encouragement, fostering a mindset of resilience and determination.

This feature complements the To-Do List by giving users both the *structure* to plan their day and the *motivation* to carry it out.

---

### 4. Site Blocker (Demo)
The final major feature is the **Site Blocker demo**. While it does not modify the system hosts file (since that requires admin-level privileges), it simulates how site blocking could work by letting users maintain a personal blacklist of distracting websites.

- Users can add websites they wish to block by entering the domain.
- Input is validated to ensure it looks like a proper URL.
- Each site appears in the user’s blocked list, with an option to remove it.

The feature acts as a **self-awareness tool**, prompting users to reflect on the sites that consume their time. This conceptual demo could easily be expanded into a full-fledged browser extension or host-file manager in the future.

---

## File Overview
The project is structured as a Flask application with the following files:

- **app.py**
  The main Flask application. It contains all routes for login, registration, logout, to-do management, motivational quotes, and the site blocker demo. Handles requests, responses, and interactions with the database.

- **helpers.py**
  Contains utility functions such as login_required decorators and input validation functions, ensuring cleaner and more maintainable code.

- **templates/**
  This folder contains all HTML files rendered by Flask using Jinja2 templates.
  - `layout.html`: The base template with navigation and Bootstrap styling.
  - `home.html`: Landing page/dashboard.
  - `login.html` and `register.html`: Authentication forms.
  - `todo.html`: Displays and manages tasks.
  - `quotes.html`: Displays motivational quotes.
  - `blocker.html`: Displays the site blocker demo with add/remove functionality.

- **static/**
  Contains custom CSS and optional JavaScript for styling beyond Bootstrap defaults.

- **azmflow.db**
  The SQLite database. Stores user credentials, tasks, and blocked sites, with relationships tied to user IDs.

---

## Design Choices
Several design decisions shaped the development of AzmFlow:

- **Database design**: Instead of using one large table, the database has separate tables for users, tasks, and blocked sites. Each entry references the `user_id` for secure, user-specific data storage.
- **Validation and error handling**: Flash messages with Bootstrap alerts provide feedback instead of showing raw errors. This ensures a polished user experience.
- **Bootstrap UI**: Using Bootstrap ensures a responsive, professional-looking interface without reinventing the wheel. Cards, buttons, and alerts create consistency across features.
- **Scope of site blocker**: While a full system-level site blocker was outside the project’s scope, a demo version was implemented to demonstrate the idea. This allows room for expansion in future iterations.

---

## Conclusion
AzmFlow is more than a coding exercise—it’s a practical productivity tool. By combining a To-Do List, Motivational Quotes, and a Site Blocker within a secure, personalized environment, it addresses three key pillars of productivity: **organization, inspiration, and focus**.

This project allowed me to apply fundamental concepts from CS50, including Flask routing, SQLite database management, user authentication, Jinja2 templating, error handling, and Bootstrap integration. It also represents a project I am proud of: one that solves a real-world challenge of staying disciplined in the face of digital distractions.

With further development, AzmFlow could expand into a full-scale productivity platform, incorporating features like reminders, calendar sync, and genuine browser-level blocking. For now, it stands as a polished, CS50-worthy demonstration of how technology can empower determination and focus.

