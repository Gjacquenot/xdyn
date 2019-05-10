#!/bin/sh
cat introduction.md interfaces.md reperes_et_conventions.md modeles_environnementaux.md courbes_de_GZ.md solver.md diffraction_radiation.md modeles_efforts.md tutorial_*.md > concatenated_doc.md
pandoc --title-prefix=XDYN --standalone --self-contained -t html --toc --toc-depth=3 --mathml --highlight-style pygments -f markdown -V lang=fr concatenated_doc.md --css stylesheet.css -o doc.html
rm -f concatenated_doc*.md
