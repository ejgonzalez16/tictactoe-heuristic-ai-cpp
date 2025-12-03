# Tic-Tac-Toe AI (C++)

Advanced Tic-Tac-Toe implementation in C++ featuring a **heuristic, look-ahead AI that never loses**.  
The AI player is guaranteed to **win or draw**, but **never lose**, thanks to a custom decision tree algorithm implemented entirely from scratch.

This project goes beyond traditional Tic-Tac-Toe by including:
- A **piece placement phase**
- A **piece movement phase**
- **Adjacency-based movement rules**
- A **recursive evaluation of all future board states**

It functions as a miniature game engine showcasing **game logic, rule systems, and AI search trees** in pure C++.

---

## 🚀 Features

### 🧠 Unbeatable AI
- The AI analyzes the board by generating a **full decision tree** using the function `generarArbol()`.
- It evaluates every possible future move and counter-move.
- Uses heuristics to choose the optimal branch.
- As a result, the AI **cannot lose** under any game state.

### 🌳 Custom Decision Tree Engine (Built From Scratch)
- All AI logic is implemented manually with:
  - Recursive tree expansion
  - Board state evaluation
  - Heuristic scoring
  - Move selection from simulated outcomes

No external libraries or frameworks — only C++ STL.

### 🎮 Unique Tic-Tac-Toe Variant
This project uses a more advanced version of Tic-Tac-Toe with:
- **3×3 board**
- 3 pieces per player
- After placement, players must **move** pieces to adjacent free cells
- Movement must be **orthogonally adjacent**
- The game is more strategic and complex than the classic version

### 🧩 Full Game Loop Implementation
Complete input/output flow:
- Choosing X or O
- Turn management
- Piece placement
- Piece movement
- Victory detection
- Draw detection
- Board printing

---

## 📂 Project Structure

- `main.cpp` → Handles the game loop, user interactions, and turn management  
- `Partida.h / Partida.cpp` → Core game rules and AI logic  
- `generarArbol()` → AI function that builds and evaluates the full move tree  

---

## 🛠️ Technologies

- **C++ (manual memory management)**
- **Recursive algorithms**
- **Game AI look-ahead**
- **Custom search tree implementation**
- **Console-based board rendering**

---

## 🥇 Why This Project Matters

This repository demonstrates:
- Strong understanding of **game AI design**
- Ability to implement **search-tree based decision systems**
- Clean **low-level C++ logic**
- A complete, working turn-based game engine
- Techniques applicable to real-world **game dev**, such as:
  - Minimax-like logic  
  - Recursive evaluation  
  - State simulation  

---
