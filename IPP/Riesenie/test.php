<?php
/**
 * IPP projekt 2
 * Richard Filo(xfilor00)
 * test.php
 */

ini_set('display_errors', 'stderr');    //Pro vypis varovani na standardni chybovy vystup

$test = new Tester();
$test->parse_args();    // parsovanie argumentov
$test->find_tests();    // najdenie testov
$test->make_test();     // spustenie testov
$test->printHTML();     // vystup v HTML

class Tester
{
    public $rec;
    public $dir;

    public $parseScript;
    public $intScript;
    public $jexamxml;
    public $jexamcfg;

    public $test_only;
    public $int_only;

    public $testDirs;
    public $tests;
    public $results;

    /*
     *  Nastavenie pociatocnych hodnot
     */
    public function __construct()
    {
        $this->rec = false;
        $this->dir = './';
        $this->parseScript = './parse.php';
        $this->intScript = './interpret.py';
        $this->jexamxml = '/pub/courses/ipp/jexamxml/jexamxml.jar';
        $this->jexamcfg = '/pub/courses/ipp/jexamxml/options';
        $this->parse_only = false;
        $this->int_only = false;

        $this->tests = [];
        $this->results = [];
    }

    /*
     *  HTML vystup
     */
    public function printHTML()
    {
       echo "
<!DOCTYPE html>
<html>
<head>
<style>
table {
    border: 2px solid;
    border-collapse: collapse;
    width: 100%;
}

th, td {
    text-align: left;
    padding: 8px;
}
body {
    margin-left: auto;
    margin-right: auto;
    max-width: 1000px;
}

tr:nth-child(even) {background-color: #f2f2f2;}
</style>
</head>
<body>

<h2>Test results</h2>

<div style=\"overflow-x:auto;\">
<table>
    <tr style=\"background-color: #698459; border-bottom-width: 2px; border-bottom-style: solid;\">
        <th>Test name</th>
        <th>Expected RC</th>
        <th>RC</th>
        <th>Result</th>
    </tr>";
    $count = count($this->results);
    $sum = 0;
    $color = "";
    foreach($this->results as $testName => $test){
        if($test[2] == 'PASS'){
            $sum += 1;
            $color = "green";
        }
        else{
            $color = "red";
        }
        
        echo "
        <tr>
            <td>$testName</td>
            <td>$test[0]</td>
            <td>$test[1]</td>
            <td><b style=\"color:$color;\">$test[2]</b></td>
        </tr>
        ";
    }
    echo "
        <tr style=\"background-color: #698459; border-top-width: 2px; border-top-style: solid;\">
            <td><b>Summary</b></td>
            <td></td>
            <td></td>
            <td><b>$sum/$count</b></td>
        </tr>
    </table>
</div>

</body>
</html>
"; 
    }

    /*
     *  Hladanie testov
     */
    public function make_test()
    {
        foreach ($this->tests as $test){
            if($this->parse_only){  //parse.php
                if (!file_exists($this->parseScript)){
                    fprintf(STDERR, "CHYBA: Subor \"".$this->parseScript."\" neexistuje!\n");
                    exit(41);
                }
                if (!file_exists($this->jexamxml)){
                    fprintf(STDERR, "CHYBA: Subor \"".$this->jexamxml."\" neexistuje!\n");
                    exit(41);
                }
                if (!file_exists($this->jexamcfg)){
                    fprintf(STDERR, "CHYBA: Subor \"".$this->jexamcfg."\" neexistuje!\n");
                    exit(41);
                }
                $Out = "";
                exec('php7.4 '.$this->parseScript.' <'.$test.'.src'.' >'.$test.'TMP.out 2>/dev/null' , $Out, $RC);
                $RCfile = fopen($test.'.rc', "r") or exit(41);
                $expRC = fread($RCfile,filesize($test.'.rc'));
                fclose($RCfile);
                if($expRC == 0){
                    exec('java -jar '.$this->jexamxml.' '.$test.'TMP.out '.$test.'.out /dev/null '.$this->jexamcfg.' 2>/dev/null', $diffOut, $diffRC);
                    if($diffRC == 0)
                        $this->results[$test] = [$expRC, $RC, "PASS"];
                    else
                        $this->results[$test] = [$expRC, $RC, "FAIL"];
                }
                else{
                    if($expRC == $RC)
                        $this->results[$test] = [$expRC, $RC, "PASS"];
                    else
                        $this->results[$test] = [$expRC, $RC, "FAIL"];
                }
                unlink($test.'TMP.out');
            }
            elseif($this->int_only){    //interpret.php
                if (!file_exists($this->intScript)){
                    fprintf(STDERR, "CHYBA: Subor \"".$this->intScript."\" neexistuje!\n");
                    exit(41);
                }
                exec('python3.8 '.$this->intScript.' --source='.$test.'.src <'.$test.'.in >'.$test.'TMP.out 2>/dev/null' , $Out, $RC);
                $RCfile = fopen($test.'.rc', "r") or exit(41);
                $expRC = fread($RCfile,filesize($test.'.rc'));
                fclose($RCfile);
                if($expRC == 0){
                    exec('diff '.$test.'TMP.out'.' '.$test.'.out 2>/dev/null', $diffOut, $diffRC);
                    if($diffRC == 0)
                        $this->results[$test] = [$expRC, $RC, "PASS"];
                    else
                        $this->results[$test] = [$expRC, $RC, "FAIL"];
                    
                }
                else{
                    if($expRC == $RC)
                        $this->results[$test] = [$expRC, $RC, "PASS"];
                    else
                        $this->results[$test] = [$expRC, $RC, "FAIL"];
                }
                unlink($test.'TMP.out');
            }
            else{   //oba
                if (!file_exists($this->parseScript)){
                    fprintf(STDERR, "CHYBA: Subor \"".$this->parseScript."\" neexistuje!\n");
                    exit(41);
                }
                if (!file_exists($this->intScript)){
                    fprintf(STDERR, "CHYBA: Subor \"".$this->intScript."\" neexistuje!\n");
                    exit(41);
                }
                $Out = "";
                exec('php7.4 '.$this->parseScript.' <'.$test.'.src'.' 2>/dev/null | python3.8 '.$this->intScript.' --input='.$test.'.in >'.$test.'TMP.out 2>/dev/null' , $Out, $RC);
                $RCfile = fopen($test.'.rc', "r") or exit(41);
                $expRC = fread($RCfile,filesize($test.'.rc'));
                fclose($RCfile);
                if($expRC == 0){
                    exec('diff '.$test.'TMP.out'.' '.$test.'.out 2>/dev/null', $diffOut, $diffRC);
                    if($diffRC == 0)
                        $this->results[$test] = [$expRC, $RC, "PASS"];
                    else
                        $this->results[$test] = [$expRC, $RC, "FAIL"];
                }
                else{
                    if($expRC == $RC)
                        $this->results[$test] = [$expRC, $RC, "PASS"];
                    else
                        $this->results[$test] = [$expRC, $RC, "FAIL"];
                }
                unlink($test.'TMP.out');
            }
        }
    }

    /*
     *  Hladanie testov
     */
    public function find_tests()
    {   
        if (!file_exists($this->dir)){
            fprintf(STDERR, "CHYBA: Subor \"".$this->dir."\" neexistuje!\n");
            exit(41);
        }

        $Directory = new RecursiveDirectoryIterator($this->dir);
        if ($this->rec)
            $Iterator = new RecursiveIteratorIterator($Directory);
        else
            $Iterator = new IteratorIterator($Directory);

        $Regex = new RegexIterator($Iterator, '/^.+\.src$/i', RecursiveRegexIterator::GET_MATCH);
        foreach ($Regex as $r)
        {
            $testName = preg_replace("/\.src$/","",$r[0]);  // odstranenie pripony .src

            $this->tests[] = $testName;
            if (!file_exists($testName.'.rc'))
                file_put_contents($testName.'.rc', "0");
            if (!file_exists($testName.'.in'))
                file_put_contents($testName.'.in', "");
            if (!file_exists($testName.'.out'))
                file_put_contents($testName.'.out', "");
        }
    }

    /*
     *  Parsovanie argumentov
     */
    public function parse_args()
    {
        global $argc, $argv;

        function usage($out)
        {
            fprintf($out, "    Skript sluzi na automaticke testovanie aplikace \"parse.php\" a \"interpret.py\".
    Skript prejde zadany adresar s testami a vyuzije ich na automaticke otestovanie
    spravnej funkcnosti jednoho ci oboch skriptou vratane vygenerovania prehladneho
    suhrnu v HTML 5 na standardny vystup.
    
    Prepinace:
    --help - vypise napovedu skriptu
    
    --directory=path  - testy bude hledat v zadanem adresari (chybi-li tento parametr,
                        tak skript prochazi aktualni adresar)
    
    --recursive - testy bude hledat nejen v zadanem adresari, ale i rekurzivne
                  ve vsech jeho podadresarich
    
    --parse-script=file - soubor se skriptem v PHP 7.4 pro analyzu zdrojoveho kodu
                          v IPP-code21 (chybi-li tento parametr, tak implicitni
                          hodnotou je parse.php ulozeny v aktualnim adresari)
    
    --int-script=file - soubor se skriptem v Python 3.8 pro interpret XML reprezentace
                        kodu v IPPcode21 (chybi-li tento parametr, tak implicitni
                        hodnotou je interpret.py ulozeny v aktualnim adresari)

    --parse-only - bude testovan pouze skript pro analyzu zdrojoveho kodu v IPPcode21
                   (tento parametr se nesmi kombinovat s --int-only a --int-script),
                   vystup s referencnim vystupem (soubor s priponou out) porovnavejte
                   nastrojem A7Soft JExamXML
    
    --int-only - bude testovan pouze skript pro interpret XML reprezentace kodu v IPPcode21
                 (tento parametr se nesmi kombinovat s --parse-only a --parse-script).
                 Vstupni program reprezentovan pomoci XML bude v souboru s priponou src
    
    --jexamxml=file - soubor s JAR balickem s nastrojem A7Soft JExamXML. Je-li vynechan
                      uvazuje se implicitni umisteni /pub/courses/ipp/jexamxml/jexamxml.jar
                      na serveru Merlin, kde bude test.php hodnocen
    
    --jexamcfg=file - soubor s konfiguraci nastroje A7Soft JExamXML. Je-li vynechan
                      uvazuje se implicitni umisteni /pub/courses/ipp/jexamxml/options
                      na serveru Merlin, kde bude test.php hodnocen\n");
        }

        $options = getopt('', ['help', 'directory:', 'recursive', 'parse-script:', 'int-script:', 'parse-only', 'int-only', 'jexamxml:', 'jexamcfg:'], $rest_index);
        if($rest_index != $argc)
        {
            usage(STDERR);
            fprintf(STDERR, "CHYBA: Chyba pri zadavani argumentov\n");
            exit(10);
        }

        $PSset = false;
        $ISset = false;

        foreach ($options as $o => $a) 
        {
            if($o == 'help'){
                if($argc == 2){
                    usage(STDOUT);
                    exit(0);
                }
                else{
                    fprintf(STDERR, "CHYBA: --help nelze kombinovat s dalsim parametrem\n");
                    exit(10);
                }
            }
            elseif ($o == 'directory') {
                $this->dir = $a;
            }
            elseif ($o == 'recursive') {
                $this->rec = true;
            }
            elseif ($o == 'parse-script') {
                $this->parseScript = $a;
                $PSset = true;
            }
            elseif ($o == 'int-script') {
                $this->intScript = $a;
                $ISset = true;
            }
            elseif ($o == 'parse-only') {
                $this->parse_only = true;
            }
            elseif ($o == 'int-only') {
                $this->int_only = true;
            }
            elseif ($o == 'jexamxml') {
                $this->jexamxml = $a;
            }
            else{
                $this->jexamcfg = $a;
            }
        }

        if(($this->parse_only and ($this->int_only or $ISset)) or ($this->int_only and ($this->parse_only or $PSset))){
            fprintf(STDERR, "CHYBA: zla kombinacia argumentov --int-only alebo --parse-only\n");
            exit(10);
        }
    }
}

?>