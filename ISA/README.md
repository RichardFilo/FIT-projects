# **Zadanie**
Společná část popisu:
Vytvořte komunikující aplikaci podle konkrétní vybrané specifikace pomocí síťové knihovny BSD sockets (pokud není ve variantě zadání uvedeno jinak). Projekt bude vypracován v jazyce C/C++. Pokud individuální zadání nespecifikuje vlastní referenční systém, musí být projekt přeložitelný a spustitelný na serveru merlin.fit.vutbr.cz pod operačním systémem GNU/Linux. Program by však měl být přenositelný. Hodnocení projektů může probíhat na jiném počítači s nainstalovaným OS GNU/Linux, včetně jiných architektur než Intel/AMD, jiných distribucí, jiných verzí knihoven apod. Pokud vyžadujete minimální verzi knihovny (dostupnou na serveru merlin), jasně tuto skutečnost označte v dokumentaci a README.

Vypracovaný projekt uložený v archívu .tar a se jménem xlogin00.tar odevzdejte elektronicky přes IS. Soubor nekomprimujte.

    Termín odevzdání je 18.11.2020 (hard deadline). Odevzdání e-mailem po uplynutí termínu, dodatečné opravy či doplnění kódu není možné.
    Odevzdaný projekt musí obsahovat:
        soubor se zdrojovým kódem (dodržujte jména souborů uvedená v konkrétním zadání),
        funkční Makefile pro překlad zdrojového souboru,
        dokumentaci (soubor manual.pdf), která bude obsahovat uvedení do problematiky, návrhu aplikace, popis implementace, základní informace o programu, návod na použití. V dokumentaci se očekává následující: titulní strana, obsah, logické strukturování textu, přehled nastudovaných informací z literatury, popis zajímavějších pasáží implementace, použití vytvořených programů a literatura.
        soubor README obsahující krátký textový popis programu s případnými rozšířeními/omezeními, příklad spuštění a seznam odevzdaných souborů,
        další požadované soubory podle konkrétního typu zadání. 
    Pokud v projektu nestihnete implementovat všechny požadované vlastnosti, je nutné veškerá omezení jasně uvést v dokumentaci a v souboru README.
    Co není v zadání jednoznačně uvedeno, můžete implementovat podle svého vlastního výběru. Zvolené řešení popište v dokumentaci.
    Při řešení projektu respektujte zvyklosti zavedené v OS unixového typu (jako je například formát textového souboru).
    Vytvořené programy by měly být použitelné a smysluplné, řádně komentované a formátované a členěné do funkcí a modulů. Program by měl obsahovat nápovědu informující uživatele o činnosti programu a jeho parametrech. Případné chyby budou intuitivně popisovány uživateli.
    Aplikace nesmí v žádném případě skončit s chybou SEGMENTATION FAULT ani jiným násilným systémovým ukončením (např. dělení nulou).
    Pokud přejímáte krátké pasáže zdrojových kódů z různých tutoriálů či příkladů z Internetu (ne mezi sebou), tak je nutné vyznačit tyto sekce a jejich autory dle licenčních podmínek, kterými se distribuce daných zdrojových kódů řídí. V případě nedodržení bude na projekt nahlíženo jako na plagiát.
    Konzultace k projektu podává vyučující, který zadání vypsal.
    Sledujte fórum k projektu, kde se může objevit dovysvětlení či upřesnění týkající se zadání.
    Před odevzdáním zkontrolujte, zda jste dodrželi všechna jména souborů požadovaná ve společné části zadání i v zadání pro konkrétní projekt. Zkontrolujte, zda je projekt přeložitelný.

Hodnocení projektu:

    Maximální počet bodů za projekt je 20 bodů.
        Maximálně 15 bodů za plně funkční aplikaci.
        Maximálně 5 bodů za dokumentaci. Dokumentace se hodnotí pouze v případě funkčního kódu. Pokud kód není odevzdán nebo nefunguje podle zadání, dokumentace se nehodnotí.
    Příklad kriterií pro hodnocení projektů:
        nepřehledný, nekomentovaný zdrojový text: až -7 bodů
        nefunkční či chybějící Makefile: až -4 body
        nekvalitní či chybějící dokumentace: až -5 bodů
        nedodržení formátu vstupu/výstupu či konfigurace: -10 body
        odevzdaný soubor nelze přeložit, spustit a odzkoušet: 0 bodů
        odevzdáno po termínu: 0 bodů
        nedodržení zadání: 0 bodů
        nefunkční kód: 0 bodů
        opsáno: 0 bodů (pro všechny, kdo mají stejný kód), návrh na zahájení disciplinárního řízení. 

Popis varianty:
Napište program dns, který bude filtrovat dotazy typu A směřující na domény v rámci dodaného seznamu a jejich poddomény. Ostatní dotazy bude přeposílat v nezměněné podobě specifikovanému resolveru. Odpovědi na dříve přeposlané dotazy bude program předávat původnímu tazateli. Analýza a sestavení DNS zpráv musí být implementována přímo v programu dns. Stačí uvažovat pouze komunikaci pomocí UDP a dotazy typu A. Na jiné typu dotazů a nežádoucí dotazy odpovídejte vhodnou chybovou zprávou.

Při vytváření programu je povoleno použít pouze knihovny pro práci se sokety a další obvyklé funkce používané v síťovém prostředí (jako je netinet/*, sys/*, arpa/* apod.), knihovnu pro práci s vlákny (pthread), signály, časem, stejně jako standardní knihovnu jazyka C (varianty ISO/ANSI i POSIX), C++ a STL. Jiné knihovny nejsou povoleny.

Spuštění aplikace
Použití: dns -s server [-p port] -f filter_file

Pořadí parametrů je libovolné. Popis parametrů:

    -s: IP adresa nebo doménové jméno DNS serveru (resolveru), kam se má zaslat dotaz.
    -p port: Číslo portu, na kterém bude program očekávat dotazy. Výchozí je port 53.
    -f filter_file: Jméno souboru obsahující nežádoucí domény.

Podporované typy dotazů

Uvažujte pouze dotazy typu A, protokol UDP a libovolné protokoly nižších vrstev podporované OS. Není požadována podpora DNSSEC.

Výstup aplikace

Program nebude vypisovat žádné informace. Volitelně však můžete implementovat parametr -v (verbose), při jehož uvedení bude program vypisovat informace o překladu ve vámi zvoleném formátu.

Formát souboru se seznamem nežádoucích domén

Nežádoucí domény budou dopředu uloženy v lokálním textovém ASCII souboru, každá doména bude uvedena na samostatném řádku. Prázdné řádky a řádky začínající znakem '#' ignorujte. Uvažujte konce řádků používané v OS GNU/Linux, Microsoft Windows i Apple Mac OS.

Příklad souborů nežádoucích domén:

    https://dbl.oisd.nl/
    https://pgl.yoyo.org/adservers/serverlist.php?hostformat=nohtml&showintro=1


Doplňující informace k zadání

    Před odevzdáním projektu si důkladně pročtěte společné zadání pro všechny projekty.
    Jakékoliv rozšíření nezapomeňte zdůraznit v souboru README a v dokumentaci. Není však možné získat více bodů, než je stanovené maximum.
    Program se musí vypořádat s chybnými vstupy.
    Veškeré chybové výpisy vypisujte srozumitelně na standardní chybový výstup.
    Pokud máte pocit, že v zadání není něco specifikováno, popište v dokumentaci vámi zvolené řešení a zdůvodněte, proč jste jej vybrali.
    V dokumentaci popište, jaké řešení jste zvolili pro procházení seznamu blokovaných domén.
    V dokumentaci uveďte, jaké chybové zprávy váš program generuje a za jakých okolností.
    Vytvořený kód by měl být modulární a otestovaný. Testy, které jste při řešení projektu napsali se spustí voláním "make test".
    Pište robustní aplikace, které budou na vstupu vstřícné k drobným odchylkám od specifikace.
    Při řešení projektu uplatněte znalosti získané v dřívějších kurzech týkající se jak zdrojového kódu (formátování, komentáře), pojmenování souborů, tak vstřícnosti programu k uživateli.

Referenční prostředí pro překlad a testování
Program by měl být přenositelný. Referenční prostředí pro překlad budou servery eva.fit.vutbr.cz a merlin.fit.vutbr.cz (program musí být přeložitelný a funkční na obou systémech). Vlastní testování může probíhat na jiném počítači s nainstalovaným OS GNU/Linux, či FreeBSD, včetně jiných architektur než Intel/AMD, jiných distribucí, jiných verzí knihoven apod. Pokud vyžadujete minimální verzi knihovny (dostupné na serveru merlin a eva), jasně tuto skutečnost označte v dokumentaci a README.

Doporučená literatura

    RFC1035

# **Hodnotenie**
* **Maximum bodu**: 20
* **Ziskano bodu**: 12
* **Komentář učitele k hodnocení**:
   * S pomocí programu se podařilo úspěšně překládat doménová jména
   * Program se úspěšně vypořádal s promíchanými odpověďmi bez filtrace
   * Program se úspěšně vypořádal s promíchanými odpověďmi s filtrací
   * Program úspěšně filtruje subdomény
   * Úspěšně přeložen 1 dotaz
   * Úspěšně přeloženy 4 dotazy
   * Úspěšně přeložen 1 nefiltrovaný dotaz
   * Úspěšně přeloženy 4 nefiltrované dotazy
   * OK_bezodpovedi.query.merlin.fit.vutbr.cz
   * Neúspěšný test bezodpovedi.query.kazi.fit.vutbr.cz
   * Neúspěšný test bezodpovedi.query.eva.fit.vutbr.cz
   * Neúspěšný test bezodpovedi.query.www.fit.vutbr.cz
   * OK_yoyo-bezodpovedi.query.merlin.fit.vutbr.cz
   * Neúspěšný test yoyo-bezodpovedi.query.kazi.fit.vutbr.cz
   * Neúspěšný test yoyo-bezodpovedi.query.eva.fit.vutbr.cz
   * Neúspěšný test yoyo-bezodpovedi.query.www.fit.vutbr.cz
   * OK_subdomeny
   * Neúspěšný test yoyo-vykon.query.1-1ads.com
   * Dotaz úspěšně odfiltrován
   * Neúspěšný test oisd-vykon.query.zzzzzzzzzzzzz.com
   * Chybná práce s pamětí
   * Informativní README
   * Modulární kód, členění do funkcí by mohlo být lepší
   * Dokumentace mohla být čitelnější, lépe popisná, příliš mnoho volného místa 