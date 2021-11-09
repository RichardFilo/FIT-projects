ICP projekt
Varianta 2: Editor a interpret hierarchicky strukturovaných funkčních bloků
Autori: Richard Filo(xfilor00) a Tomas Lisicky(xlisic01)

Richard Fiľo:
	* tvorba aplikačného rozhrania (block.h, block_schema.h)
	* grafická reprezentácia pinov/portov blokov (pin.h)

Tomáš Lisický:
	* návrh a tvorba uživateľského rozhrania (main.cpp, mainwindow.h, main.window.ui)
	* grafická implementácia blokov (GraphicBlock.h)

Úvod:
	Pre tvorbu našeho blokového schématu sme si vybrali bloky na sčítanie(SUM), odčítanie(SUB), inkrementáciu(INC) a dekrementáciu(DEC) celočíselných hodnôt (integer). Myslíme si, že tieto bloky sú postačujúce z hľadiska demonštrácie funkčnosti.
	
Ovládanie:
	CTRL+kolečko - vzdiaľuje / približuje pohľad.

	Pridávanie blokov do schémy pomocou tlačidieľ v ľavom hornom rohu.
	Bloky sa môžu presúvať držaním myši na danom bloku.
	Dvojklikom na blok môžeme upraviť jeho meno.
	
	Bloky majú piny a porty, prepájať jednotlivé bloky môžeme kliknutím prv na výstup(port) a následnym kliknutím na vstup(pin) iného bloku.
	Dvojklikom na vstup(pin) môžeme určit jeho počiatočnú hodnotu.
	PO PREPOJENÍ BLOKOV SA UŽ BLOKY NEBUDÚ MÔCŤ PRESÚVAŤ!
	
	V pravom hornom rohu rozhrania je tlačidlo "simulate", ktorého stlačením sa otvorí dialógové okno, kde uživateľ určí výstupný súbor kam sa vygeneruje C++ reprezentácia daného schématu.
	
Simulácia:
	Vygenerovaný výstupny súbor preložíme pomocou "g++ [meno_súboru] -o [prelož. súbor] block.o block_schema.o".
	Na preklad súboru je treba mať dostupné preložené moduly "block.o" a "block_schema.o" a taktiež ich hlavičkové súbory v zložke, v ktorej sa vykoná preklad.
	
	Po spustení programu [prelož. súbor] sa vypíše na štandardný výstup obsah množiny blokov spolu s obsahom množiny spojov (alebo inak, uzlov).
	Následuje priebeh simulácie krok za krokom.
	Vstupy(piny) blokov majú predvolenú "nedefinovanú" hodnotu - tieto hodnoty sa menia počas simulácie, a teda výpočtami blokov na ktorý je daný blok pripojený (alebo uživateľ explicítne zadal hodnotu pri dvojkliku na pin).
	Ak pri výpočte má aspoň jeden vstup "nedefinovanú" hodnotu, výstup bude tiež "nedefinovaný".
	Na konci simulácie sa vypíše konečný stav všetkých blokov.
	
Neimplementovaná funkcionalita:
	* Cyklická závislosť blokov.
	* Zobrazenie knižnice blokov / kategórie.
