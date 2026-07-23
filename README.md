# 📝 ToDo List Application (C++ / Qt)

Nowoczesna, stacjonarna aplikacja do zarządzania zadaniami napisana w języku **C++** z wykorzystaniem frameworka **Qt** oraz wzorca **Model-View-Controller (MVC)**. Projekt kładzie duży nacisk na czystą architekturę, wydajne przetwarzanie danych w pamięci RAM oraz dbałość o detale interfejsu użytkownika (UX).

---

## 🚀 Główne Funkcje

* **Pełny cykl CRUD:** Dodawanie, przeglądanie, oznaczanie jako ukończone oraz usuwanie zadań z automatyczną synchronizacją w bazie **SQLite**.
* **Filtrowanie i Sortowanie w czasie rzeczywistym:** Płynne wyszukiwanie zadań po nazwie oraz automatyczne spychanie wykonanych zadań na dół listy za pomocą `QSortFilterProxyModel`.
* **Dynamiczny Pasek Postępu:** Automatyczne przeliczanie i wizualizacja procentowego wykonania planu zadań w oparciu o analizę stanu modelu.
* **Customowe Stylizowanie Komórek (Subclassing):** Własny model `TaskModel` dziedziczący po `QSqlTableModel`, który dynamicznie modyfikuje wygląd komórek (przekreślenie czcionki, zmiana koloru na szary) na podstawie ról Qt (`Qt::FontRole`, `Qt::ForegroundRole`).
* **Przełącznik Motywów:** Obsługa trybu ciemnego (Dark Mode) oraz jasnego zmodyfikowanego za pomocą arkuszy stylów Qt CSS (QSS).
* **Szlify Ergonomiczne (UX):** Automatyczny focus na pole tekstowe po dodaniu zadania, skrót klawiszowy **Enter** oraz dynamiczne blokowanie/odblokowywanie przycisków w zależności od wyboru na liście.

---

## 🛠️ Architektura i Rozwiązania Techniczne

Aplikacja została zaprojektowana z zachowaniem ścisłej separacji odpowiedzialności (Single Responsibility Principle):

* **`DatabaseManager` (Data Layer):** Odpowiada za zestawianie połączenia z bazą danych SQLite, tworzenie schematu tabel oraz wykonywanie operacji SQL.
* **`TaskModel` (Model Layer):** Klasa pochodna `QSqlTableModel`. Nadpisuje metodę `data()`, pozwalając na wstrzykiwanie logiki wizualnej dla zrobionych zadań bezpośrednio w warstwie danych widoku, bez zanieczyszczania kodu interfejsu.
* **`QSortFilterProxyModel` (Proxy Layer):** Działa jako warstwa pośrednia między modelem źródłowym a widokiem. Odpowiada za sortowanie i filtrowanie wpisów w pamięci RAM bez powtarzania ciężkich zapytań do dysku.
* **`MainWindow` (View/Controller Layer):** Obsługuje zdarzenia interfejsu (sygnały i sloty) oraz zarządza stanem kontrolek UI.

---

## 🧰 Użyte Technologie

* **Język:** C++17
* **Framework:** Qt 6 / Qt 5 (Moduły: `Core`, `Gui`, `Widgets`, `Sql`)
* **System budowania:** CMake
* **Baza danych:** SQLite3
