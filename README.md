# Object-Oriented Programming Evolution in C++
Three modular projects demonstrating advanced OOP architectures, inheritance hierarchies, and modern C++ features (STL, Templates, Singleton, and Exception Handling).

NOTE: Code comments, classes, and variables are written in Romanian per project requirements.

**Project 1 — Summary**
- **Goal:** Mini-application with at least 4 related classes, demonstrating encapsulation and operator overloading.
- **Requirements (brief):** 4+ classes; default/full/partial/copy constructors; destructor; assignment; stream and indexing operators; increment/decrement; at least two arithmetic operators; a conditional operator; type cast; getters/setters for at least 2 classes; use primitive types and pointers (no STL containers).
- **Implementation:** `Adr` (address), `Client` (contains `Adr`), `Fir` (yarn type), `Produs` (product, dynamic array of yarn IDs), `Comanda` (order, contains `Client` and dynamic array of product IDs).
- **CRUD:** Manage addresses, clients, yarns, products, orders.
- **Features:** Validate addresses; check client completeness; test yarn color availability; compute product price with tax; find the most expensive product in an order.
- **Menu:** Navigate with Up/Down and Enter; menu refreshes on keypress; text input when required.

**Project 2 — Summary**
- **Goal:** Mini-application with at least 5 classes, demonstrating inheritance, virtualization, and polymorphism with an abstract interface.
- **Requirements (brief):** 5+ classes; default/full/copy constructors; assignment; destructor; stream operators; virtual methods; inheritance (≥3 classes); polymorphism; one abstract class/interface; at least one multiple inheritance case.
- **Implementation:** `Interface` (UI and global utilities), `Card` (base), `CardEconomii` (savings), `CardDebit` (debit), `CardIncorporat` (combined savings & debit), `CardCredit` (credit).
- **CRUD:** Manage savings, debit, incorporated, and credit accounts.
- **Features:** Transactions; verify account numbers; check annual interest and bonuses; recalculate rates for incorporated accounts; compute yearly credit bill.
- **Menu:** Up/Down + Enter navigation; menu refreshes on keypress.

**Project 3 — Summary**
- **Goal:** Mini-application with at least 4 classes using STL, templates, casting, and a Singleton menu.
- **Requirements (brief):** 4+ classes; use `vector`, `set`, `list`, `map`; Singleton console menu; at least one template class and two template methods; show upcasting/downcasting; inheritance up to a grandparent; HasA/IsA relationships; constructors, copy, assignment, destructor, stream operators; robust exception handling (≥6 exceptions, at least 3 distinct types).
- **Implementation:** `Produs`, `Haina`, `Bluza`, `Pantaloni`, `Accesoriu`, `Cercei`, `Lant`, template `Colectie`, `Inventar` (Singleton); exceptions `excIntrodVal`, `excIntrodOpt`, and others.
- **CRUD:** Manage blouses, trousers, earrings, necklaces.
- **Features:** Add products to collections; view inventory and collections; list product names and prices.
- **Menu:** Simple Singleton-driven console menu; minimal refresh behavior due to time constraints.


