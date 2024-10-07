# RPI
* Dokumentacja: ``https://docs.google.com/document/d/16r9baTvD5L6q9c8by-x-md48kzLTodT6jtipIFAVy_s/edit``

# Wymagane programy
* Visual Studio Community
# Jak włączyć projekt
* Po sklonowaniu projektu wejdź do folderu RPI nastepnie OpenEngine3D i włącz plik OpenEngine3D.sln w programie Visual Studio Community

# Poruszanie się po programie:
## Klasa Display:
Klasa Display pozwala na wyświetlanie okna aplikacji.
Posiada funkcje:
* ``Display(<szerokość w pikselach>, <wysokość w pikselach>, <tytuł>)`` - tworzy okno i jego kontekst
* ``~Display()`` - Zamyka okno usuwając dane kontekstu i okna
* ``SetColor(<red>, <green>, <blue>, <alpha>)``- Ustawia kolor tła okna
* ``IsClosed()`` - zwraca zmienną boolean w zależności czy okno jest zamknięte czy otwarte
* ``Update()`` - aktualizuje okno