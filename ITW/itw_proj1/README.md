# **Zadanie**

Cílem projektu je vyzkoušet si základní znalosti jazyka CSS, jednotlivých CSS pravidel a schopnost aplikovat různé typy CSS selektorů.

1.  Stáhněte si archiv [`itw_proj1.zip`](itw_proj1.zip) a rozbalte. Archiv obsahuje:

    1.  soubor `index.html` reprezentující obsah a strukuturu webové prezentace fiktivní společnosti poskytující přepravu nákladu a zboží,
    2.  adresář `img/` obsahující použité ilustrace,
    3.  adresář `css/` obsahující prázdný soubor style.css.
2.  Implementujte soubor `style.css` bez nutnosti modifikace souboru `index.html` a přiložených obrázků tak, aby výsledná webová prezentace "pokud možno" odpovídala následujícím snímkům a popisu.

    *   [768px](768px.png), [1200px](1200px.png), [1920px](1920px.png)
    *   pozn. #1: soubor `index.html` není žádané modifikovat, i když by se to v některých případech mohlo jevit jako smysluplnější řešení a v praxi byste tak pravděpodobně učinili; chápejte nicméně toto zadání spíše jako cvičení, v kterém si vyzkoušíte různé možnosti jazyka CSS (zejména práci s CSS selektory); možnost navrhnout si celou strukturu dle sebe dostanete v druhém projektu
    *   pozn. #2: není nutné pracovat s přesností na pixely (bude hodnocena především znalost principů)

### Všeobecné vlastnosti webové prezentace

*   šířka stránky se musí plynule přizpůsobit šířce okna prohlížeče:
    *   minimální: `768px` (při nižších velikostech je možné zobrazit horizontální scrollbar)
    *   maximální: `1200px` (při vyšších velikostech bude stránka zarovnána na střed okna prohlížeče)
*   levý a pravý okraj stránky: `20px`
*   mezery mezi sloupci: `40px`
*   použitá písma:
    1.  `Merriweather` - základní - odstavce, běžný text
    2.  `Montserrat` - nadpisy, odkazy, menu, tlačítka
    3.  pozn.: soubor `index.html` již obsahuje import příslušných písem z [Google Fonts](https://fonts.google.com/)
*   základní velikosti písem:
    *   běžný text v odstavcích:
        *   velikost písma: `14px`
        *   výška řádku: `1.7`
    *   nadpisy: viz níže
    *   tlačítka (`#news-btn`, `#submit-btn`)
        *   velikost textu: `13px`
        *   mezera mezi písmeny: `.15em`
*   základní použité barvy:
    *   `#898989` - běžný text v odstavcích
    *   `#bfbfbf` - světlejší text v odstavcích
    *   `#4d4d4d` - nadpisy, odstavce v `#references`
    *   `steelblue` - odkazy
    *   `black` - odkazy po najetí myší

Některé výše zmíněné vlastnosti mohly být přetížené v jednotlivých částech dokumentu.

### Specifické vlastnosti jednotlivých částí dokumentu

1.  `#navigation`
    *   horní, spodní okraj: `20px`
    *   logo:
        *   písmo: `25px`, `black`
    *   menu:
        *   vzdálenost mezi položkami menu: `20px`
        *   písmo: `13px` (stejné jako u tlačítek)
        *   mezera mezi písmeny: `.05em`
    *   logo a menu jsou vertikálně zarovnány na střed
2.  `#header`
    *   titulek:
        *   písmo: `32px`, `white`
        *   odsazení zespodu a zleva: `20px`
3.  `#about`
    *   horní, spodní okraj: `40px`, `100px`
    *   písmo - `h2`: `40px`, `h3`: `24px`
    *   šířka sloupce: `1/3`
4.  `#middle-sections`
    *   horní, spodní okraj: `40px`, `100px`
    *   pozadí: `whitesmoke`
    *   písmo - `h2`: `32px`, `h3`: `24px`
5.  `#news`
    *   šířka: `3/5`
    *   písmo: `.news-date`: `12px`,
    *   čára: `1px`, `#e3e3e3`
    *   mezera mezi položkami: `20px`
    *   tlačítko: `lightsteelblue`
6.  `#references`
    *   šířka: `2/5`
    *   mezera mezi položkami: `40px`
    *   šířka obrázku: `120px`
    *   horizontální mezera mezi textem a obrázek: `20px`
    *   písmo autora citace: `14px`
7.  `#steps`
    *   horní, spodní okraj: `40px`, `100px`
    *   šířka sloupce: `1/3`
    *   ikony [Font Awesome](https://fontawesome.com/): `60px`, `lightsteelblue`
    *   titulek: `14px`
    *   `.steps-more`: `11px`
8.  `#contact`
    *   horní, spodní okraj: `40px`, `100px`
    *   pozadí: `#262626`
    *   šířka sloupce: `1/3`
    *   titulek: `24px`, `white`
    *   odkaz po najetí myší: `white`
    *   input - výška: `54px`, písmo: `18px`, mezera mezi inputy: `4px`
    *   písmo nevalidního e-mailu: `red`
    *   tlačítko - pozadí: `steelblue`, písmo: `white`, zaoblení: `4px`
9.  `#footer-note`
    *   horní, spodní okraj: `20px`
    *   pozadí: `#1a1a1a`
    *   text: `12px`

Vlastnosti, které nejsou výše specifikovány se pokuste odhadnout z uvedených snímků (není nutné, aby bylo na pixel přesné - viz. pozn. #2)

# **Hodnotenie**
* **Maximum bodu**: 20
* **Ziskano bodu**: 17
* **Komentář učitele k hodnocení**:
   * footer - nadpisy a search box nejsou vertikálně zarovnané
   * section reference špatné zarovnání 