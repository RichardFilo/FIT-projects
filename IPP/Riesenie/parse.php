<?php
ini_set('display_errors', 'stderr');    //Pro výpis varování na standardní chybový výstup

parse_args();   // parsovanie argumentov

$analyzator = new Analyzator();
$analyzator->checkHeader();
$xml = new XMLoutput();

while ($analyzator->analyze()) {
    //echo "Opcode:'".$analyzator->iOpcode."'\n";
    $xml->addInstruction($analyzator->iOpcode, $analyzator->iArgs); //spracovanie instukcie
}

$xml->printXML();   //vypis XML dokumentu

/*
 * Parsovanie argumentov
 */
function parse_args(){
    global $argc, $argv;
    
    if ($argc == 1) {    //bez argumentov
        return;
    }
    elseif ($argc == 2 and $argv[1]=="--help") {    //jeden argument a to --help
        echo "Skript typu filtr nacte ze standardniho vstupu zdrojovy kod v IPP-code21,\nzkontroluje lexikalni a syntaktickou spravnost kodu\na vypise na standardni vystup XML reprezentaci programu.\n\n";
        echo "--help - napoveda skriptu\n";
        exit(0);
    }
    else {  //vsetko ostatne
        fprintf(STDERR, "Chyba pri zadavani argumentov\n");
        exit(10);
    }
}
/*
 * Trieda pre analyzu prikazu 
 */
class Analyzator{

    public $iOpcode;
    public $iArgs;

    public function checkHeader()
    {
        $line = fgets(STDIN);  //nacitanie riadku
        if ($line == false){ 
            fprintf(STDERR, "Chybejici hlavicka ve zdrojovem kodu zapsanem v IPPcode21!\n");
            exit(21);
        }
        if (strpos($line, '#') !== false) { //odstranenie komentarov
            $line = explode('#', $line);
            $line = $line[0];
        }
        $line = trim($line);    //odstranenie medzier z okrajov
        //echo "-->".$line."<--";
        if ($line == "")
            $this->checkHeader();
        elseif ($line == ".IPPcode21")
            return;
        else {
            fprintf(STDERR, "Chybna nebo chybejici hlavicka ve zdrojovem kodu zapsanem v IPPcode21!\n");
            exit(21);
        }
    }
    
    public function analyze()
    {
        $line = fgets(STDIN);  //nacitanie riadku
        if ($line == false) {   //koniec vstupu
            return false;
        }

        if (strpos($line, '#') !== false) { //odstranenie komentarov
            $line = explode('#', $line);
            $line = $line[0];
        }
        $line = preg_replace('/\s+/', ' ', $line);  //odstranenie prebytocnych medzier
        $line = trim($line);    //odstranenie medzier z okrajov
        //echo "-->".$line."<--";
        if ($line == "")    //prazdny riadok
            return $this->analyze();

        $items = explode(' ', $line);
        
        if ($this->isCorect($items))
            return true;
        
        else {
            fprintf(STDERR, "Jina lexikalni nebo syntakticka chyba zdrojoveho kodu zapsaneho v IPPcode21!\n");
            exit(23);
        }
    }
    
    private function isCorect($items){
        $this->iArgs = array();

        switch ($items[0] = strtoupper($items[0])) {
            case 'MOVE':    //<var> <symb>
                if (count($items) == 3) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]) && $this->checkSymb($items[2]);
                }
                else
                    return false;
                break;

            case 'CREATEFRAME':
                if (count($items) == 1) {
                    $this->iOpcode = $items[0];
                    return true;
                }
                else
                    return false;
                break;

            case 'PUSHFRAME':
                if (count($items) == 1) {
                    $this->iOpcode = $items[0];
                    return true;
                }
                else
                    return false;
                break;
            
            case 'POPFRAME':
                if (count($items) == 1) {
                    $this->iOpcode = $items[0];
                    return true;
                }
                else
                    return false;
                break;

            case 'DEFVAR':    //<var>
                if (count($items) == 2) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]);
                }
                else
                    return false;
                break;

            case 'CALL':    //<label>
                if (count($items) == 2) {
                    $this->iOpcode = $items[0];
                    return $this->checkLabel($items[1]);
                }
                else
                    return false;
                break;

            case 'RETURN':
                if (count($items) == 1) {
                    $this->iOpcode = $items[0];
                    return true;
                }
                else
                    return false;
                break;

            case 'PUSHS':    //<symb>
                if (count($items) == 2) {
                    $this->iOpcode = $items[0];
                    return $this->checkSymb($items[1]);
                }
                else
                    return false;
                break;
            
            case 'POPS':    //<var>
                if (count($items) == 2) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]);
                }
                else
                    return false;
                break;

            case 'ADD':    //<var> <symb> <symb>
                if (count($items) == 4) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]) && $this->checkSymb($items[2]) && $this->checkSymb($items[3]);
                }
                else
                    return false;
                break;

            case 'SUB':    //<var> <symb> <symb>
                if (count($items) == 4) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]) && $this->checkSymb($items[2]) && $this->checkSymb($items[3]);
                }
                else
                    return false;
                break;

            case 'MUL':    //<var> <symb> <symb>
                if (count($items) == 4) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]) && $this->checkSymb($items[2]) && $this->checkSymb($items[3]);
                }
                else
                    return false;
                break;

            case 'IDIV':    //<var> <symb> <symb>
                if (count($items) == 4) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]) && $this->checkSymb($items[2]) && $this->checkSymb($items[3]);
                }
                else
                    return false;
                break;

            case 'LT':    //<var> <symb> <symb>
                if (count($items) == 4) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]) && $this->checkSymb($items[2]) && $this->checkSymb($items[3]);
                }
                else
                    return false;
                break;

            case 'GT':    //<var> <symb> <symb>
                if (count($items) == 4) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]) && $this->checkSymb($items[2]) && $this->checkSymb($items[3]);
                }
                else
                    return false;
                break;

            case 'EQ':    //<var> <symb> <symb>
                if (count($items) == 4) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]) && $this->checkSymb($items[2]) && $this->checkSymb($items[3]);
                }
                else
                    return false;
                break;

            case 'AND':    //<var> <symb> <symb>
                if (count($items) == 4) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]) && $this->checkSymb($items[2]) && $this->checkSymb($items[3]);
                }
                else
                    return false;
                break;
                
            case 'OR':    //<var> <symb> <symb>
                if (count($items) == 4) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]) && $this->checkSymb($items[2]) && $this->checkSymb($items[3]);
                }
                else
                    return false;
                break;

            case 'NOT':    //<var> <symb>
                if (count($items) == 3) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]) && $this->checkSymb($items[2]);
                }
                else
                    return false;
                break;

            case 'INT2CHAR':    //<var> <symb>
                if (count($items) == 3) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]) && $this->checkSymb($items[2]);
                }
                else
                    return false;
                break;

            case 'STRI2INT':    //<var> <symb> <symb>
                if (count($items) == 4) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]) && $this->checkSymb($items[2]) && $this->checkSymb($items[3]);
                }
                else
                    return false;
                break;

            case 'READ':    //<var> <type>
                if (count($items) == 3) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]) && $this->checkType($items[2]);
                }
                else
                    return false;
                break;

            case 'WRITE':    //<symb>
                if (count($items) == 2) {
                    $this->iOpcode = $items[0];
                    return $this->checkSymb($items[1]);
                }
                else
                    return false;
                break;

            case 'CONCAT':    //<var> <symb> <symb>
                if (count($items) == 4) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]) && $this->checkSymb($items[2]) && $this->checkSymb($items[3]);
                }
                else
                    return false;
                break;

            case 'STRLEN':    //<var> <symb>
                if (count($items) == 3) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]) && $this->checkSymb($items[2]);
                }
                else
                    return false;
                break;

            case 'GETCHAR':    //<var> <symb> <symb>
                if (count($items) == 4) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]) && $this->checkSymb($items[2]) && $this->checkSymb($items[3]);
                }
                else
                    return false;
                break;

            case 'SETCHAR':    //<var> <symb> <symb>
                if (count($items) == 4) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]) && $this->checkSymb($items[2]) && $this->checkSymb($items[3]);
                }
                else
                    return false;
                break;

            case 'TYPE':    //<var> <symb>
                if (count($items) == 3) {
                    $this->iOpcode = $items[0];
                    return $this->checkVar($items[1]) && $this->checkSymb($items[2]);
                }
                else
                    return false;
                break;

            case 'LABEL':    //<label>
                if (count($items) == 2) {
                    $this->iOpcode = $items[0];
                    return $this->checkLabel($items[1]);
                }
                else
                    return false;
                break;

            case 'JUMP':    //<label>
                if (count($items) == 2) {
                    $this->iOpcode = $items[0];
                    return $this->checkLabel($items[1]);
                }
                else
                    return false;
                break;

            case 'JUMPIFEQ':    //<label> <symb> <symb>
                if (count($items) == 4) {
                    $this->iOpcode = $items[0];
                    return $this->checkLabel($items[1]) && $this->checkSymb($items[2]) && $this->checkSymb($items[3]);
                }
                else
                    return false;
                break;
    
            case 'JUMPIFNEQ':    //<label> <symb> <symb>
                if (count($items) == 4) {
                    $this->iOpcode = $items[0];
                    return $this->checkLabel($items[1]) && $this->checkSymb($items[2]) && $this->checkSymb($items[3]);
                }
                else
                    return false;
                break;

            case 'EXIT':    //<symb>
                if (count($items) == 2) {
                    $this->iOpcode = $items[0];
                    return $this->checkSymb($items[1]);
                }
                else
                    return false;
                break;

            case 'DPRINT':    //<symb>
                if (count($items) == 2) {
                    $this->iOpcode = $items[0];
                    return $this->checkSymb($items[1]);
                }
                else
                    return false;
                break;

            case 'BREAK':
                if (count($items) == 1) {
                    $this->iOpcode = $items[0];
                    return true;
                }
                else
                    return false;
                break;

            default:
                fprintf(STDERR, "Neznamy nebo chybny operacni kod \"".$items[0]."\" ve zdrojovem kodu zapsanem v IPPcode21!\n");
                exit(22);
        }
    }

    private function checkSymb($symb) {
        if (preg_match('/^(int|bool|string|nil)@.*$/', $symb)) {    //konstanta
            $symb = explode('@', $symb, 2);
            if ($symb[0] == 'int') {
                if ($symb[1] == "")
                    return false;
                else {
                    array_push($this->iArgs, array($symb[0], $symb[1]));
                    return true;
                }
            }
            elseif ($symb[0] == 'bool') {
                if (preg_match('/^(true|false)$/', $symb[1])) {
                    array_push($this->iArgs, array($symb[0], $symb[1]));
                    return true;
                }
            }
            elseif ($symb[0] == 'nil') {
                if ($symb[1] == 'nil') {
                    array_push($this->iArgs, array($symb[0], $symb[1]));
                    return true;
                }
            }
            else { // 'string'
                if (preg_match('/^(\\\\[0-9]{3}|[^\\\\])*$/', $symb[1])) {
                    array_push($this->iArgs, array($symb[0], $symb[1]));
                    return true;
                }
            }
        }
        else    //premenna
            return $this->checkVar($symb);
    }

    private function checkLabel($label) {
        if (preg_match('/^(\_|\-|\$|\&|\%|\*|\!|[a-zA-Z])(\_|\-|\$|\&|\%|\*|\!|[a-zA-Z0-9])*$/', $label)) { 
            array_push($this->iArgs, array("label", $label));
            return true;
        }
        else
            return false;
    }

    private function checkType($type) {
        if (preg_match('/^(int|bool|string|nil)$/', $type)) {
            array_push($this->iArgs, array("type", $type));
            return true;
        }
        else
            return false;
    }

    private function checkVar($var) {
        if (preg_match('/^(GF|LF|TF)@(\_|\-|\$|\&|\%|\*|\!|[a-zA-Z])(\_|\-|\$|\&|\%|\*|\!|[a-zA-Z0-9])*$/', $var)) { 
            array_push($this->iArgs, array("var", $var));
            return true;
        }
        else
            return false;
    }
}

class XMLoutput{
    private $order;
    private $xml;
    private $program;

    public function __construct() {
        $this->order = 1;

        $this->xml = new DOMDocument("1.0", "UTF-8");   //tvorba dokumentu
        $this->program = $this->xml->createElement("program");  //element program
        $this->program->setAttribute("language", "IPPcode21");  //nastavenie jazyka na IPPcode21
    }

    public function addInstruction($iOpcode, $iArgs){
        $ins = $this->xml->createElement("instruction");    //element instruction
        $ins->setAttribute("order", $this->order);  //nastavenie order
        $ins->setAttribute("opcode", $iOpcode); //nastavenie opcode

        $argNum = 1;
        foreach ($iArgs as $arg){   //pridanie argumentov
            $argElement = $this->xml->createElement("arg".$argNum, $arg[1]);
            $argElement->setAttribute("type", $arg[0]);

            $ins->appendChild($argElement);
            $argNum += 1;
        }

        $this->program->appendChild($ins);
        $this->order += 1;
    }

    public function printXML()
    {
        $this->xml->appendChild($this->program);

        $this->xml->preserveWhiteSpace = false;
        $this->xml->formatOutput = true;
        echo $this->xml->saveXML();
    }
}

?>