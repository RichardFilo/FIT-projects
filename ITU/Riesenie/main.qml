import QtQuick 2.12
import QtQuick.Controls 2.5


ApplicationWindow {
    width: 800
    height: 600
    visible: true
    maximumHeight: 600
    maximumWidth: 800

    minimumHeight: 600
    minimumWidth: 800
    color: "#19b7f3"
    title: "Checkers"

    property var userName : textInput.text
    property var blackColor : "#474046";
    property var whiteColor : "#ffffff";
    property var blackFigureColor : "#000000";
    property var whiteFigureColor : "#e0e0e0";

    property var player1: "Player1"
    property var player2: "Player2"
    property var onTurn: false
    property var gameId : 0
    property var isOnline : false
    property var figureColor: "w"




    function printBoard(board){
        var ch = ["a","b","c","d","e","f","g","h"];
        var n = ["1","2","3","4","5","6","7","8"];
        var dict = {};
        for (var i=0; i<8; i++)
            for (var j=0; j<8; j++){
                var key = ch[j] + n[i]
                dict[key] = board[(j+8*i)*2] + board[(j+8*i)*2+1]
            }
        for(var keyy in dict) {
            console.log(keyy + " : " + dict[keyy]);

            var figure = dict[keyy][0];
            var color = dict[keyy][1];
            switch(figure) {
                case "0":
                figure = [whiteFigureColor, true];
                break;
                case "1":
                figure = [blackFigureColor, true];
                break;
                case "2":
                figure = ["#34f94c", true];
                break;
                case "3":
                figure = ["#f21f19", true];
                break;
                default:
                figure = ["#ffffff", false];
            }
            switch(color) {
                case "1":
                color = "#92f924";
                break;
                case "2":
                color = "#f13910";
                break;
                case "3":
                color = "#f1ba10";
                break;
                case "4":
                color = "#644e05";
                break;
                default:
                color = blackColor;
            }
            dict[keyy] = [figure, color]
            console.log(keyy + " : " + dict[keyy]);
        }

        a1Figure.color = dict["a1"][0][0]
        a1Figure.visible = dict["a1"][0][1]
        a1.color = dict["a1"][1]

        c1Figure.color = dict["c1"][0][0]
        c1Figure.visible = dict["c1"][0][1]
        c1.color = dict["c1"][1]

        e1Figure.color = dict["e1"][0][0]
        e1Figure.visible = dict["e1"][0][1]
        e1.color = dict["e1"][1]

        g1Figure.color = dict["g1"][0][0]
        g1Figure.visible = dict["g1"][0][1]
        g1.color = dict["g1"][1]

        b2Figure.color = dict["b2"][0][0]
        b2Figure.visible = dict["b2"][0][1]
        b2.color = dict["b2"][1]

        d2Figure.color = dict["d2"][0][0]
        d2Figure.visible = dict["d2"][0][1]
        d2.color = dict["d2"][1]

        f2Figure.color = dict["f2"][0][0]
        f2Figure.visible = dict["f2"][0][1]
        f2.color = dict["f2"][1]

        h2Figure.color = dict["h2"][0][0]
        h2Figure.visible = dict["h2"][0][1]
        h2.color = dict["h2"][1]

//##############################################

        a3Figure.color = dict["a3"][0][0]
        a3Figure.visible = dict["a3"][0][1]
        a3.color = dict["a3"][1]

        c3Figure.color = dict["c3"][0][0]
        c3Figure.visible = dict["c3"][0][1]
        c3.color = dict["c3"][1]

        e3Figure.color = dict["e3"][0][0]
        e3Figure.visible = dict["e3"][0][1]
        e3.color = dict["e3"][1]

        g3Figure.color = dict["g3"][0][0]
        g3Figure.visible = dict["g3"][0][1]
        g3.color = dict["g3"][1]

        b4Figure.color = dict["b4"][0][0]
        b4Figure.visible = dict["b4"][0][1]
        b4.color = dict["b4"][1]

        d4Figure.color = dict["d4"][0][0]
        d4Figure.visible = dict["d4"][0][1]
        d4.color = dict["d4"][1]

        f4Figure.color = dict["f4"][0][0]
        f4Figure.visible = dict["f4"][0][1]
        f4.color = dict["f4"][1]

        h4Figure.color = dict["h4"][0][0]
        h4Figure.visible = dict["h4"][0][1]
        h4.color = dict["h4"][1]

//##############################################

        a5Figure.color = dict["a5"][0][0]
        a5Figure.visible = dict["a5"][0][1]
        a5.color = dict["a5"][1]

        c5Figure.color = dict["c5"][0][0]
        c5Figure.visible = dict["c5"][0][1]
        c5.color = dict["c5"][1]

        e5Figure.color = dict["e5"][0][0]
        e5Figure.visible = dict["e5"][0][1]
        e5.color = dict["e5"][1]

        g5Figure.color = dict["g5"][0][0]
        g5Figure.visible = dict["g5"][0][1]
        g5.color = dict["g5"][1]

        b6Figure.color = dict["b6"][0][0]
        b6Figure.visible = dict["b6"][0][1]
        b6.color = dict["b6"][1]

        d6Figure.color = dict["d6"][0][0]
        d6Figure.visible = dict["d6"][0][1]
        d6.color = dict["d6"][1]

        f6Figure.color = dict["f6"][0][0]
        f6Figure.visible = dict["f6"][0][1]
        f6.color = dict["f6"][1]

        h6Figure.color = dict["h6"][0][0]
        h6Figure.visible = dict["h6"][0][1]
        h6.color = dict["h6"][1]

//##############################################

        a7Figure.color = dict["a7"][0][0]
        a7Figure.visible = dict["a7"][0][1]
        a7.color = dict["a7"][1]

        c7Figure.color = dict["c7"][0][0]
        c7Figure.visible = dict["c7"][0][1]
        c7.color = dict["c7"][1]

        e7Figure.color = dict["e7"][0][0]
        e7Figure.visible = dict["e7"][0][1]
        e7.color = dict["e7"][1]

        g7Figure.color = dict["g7"][0][0]
        g7Figure.visible = dict["g7"][0][1]
        g7.color = dict["g7"][1]

        b8Figure.color = dict["b8"][0][0]
        b8Figure.visible = dict["b8"][0][1]
        b8.color = dict["b8"][1]

        d8Figure.color = dict["d8"][0][0]
        d8Figure.visible = dict["d8"][0][1]
        d8.color = dict["d8"][1]

        f8Figure.color = dict["f8"][0][0]
        f8Figure.visible = dict["f8"][0][1]
        f8.color = dict["f8"][1]

        h8Figure.color = dict["h8"][0][0]
        h8Figure.visible = dict["h8"][0][1]
        h8.color = dict["h8"][1]
    }

    function getRooms(){
        var xmlhttp = new XMLHttpRequest();
        var url = "http://adambarca123.pythonanywhere.com/game/";

        xmlhttp.onreadystatechange=function() {
            if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {
                myFunction(xmlhttp.responseText);
            }
        }
        xmlhttp.open("GET", url, true);
        xmlhttp.send();
    }

    function myFunction(json) {
        var obj = JSON.parse(json);
        console.log(json)
        console.log(obj.rooms)
        roomsListView.model.clear();
        for (var i in obj.rooms){
            console.log(obj.rooms[i].id, obj.rooms[i].player)
            roomsListView.model.append( {roomId: obj.rooms[i].id, player: obj.rooms[i].player })
        }
        roomView.visible   = true
    }

    function addRoom(){
        var xmlhttp = new XMLHttpRequest();
        var url = "http://adambarca123.pythonanywhere.com/game/";
        var data = JSON.stringify({"name": userName});

        xmlhttp.onreadystatechange=function() {
            if (xmlhttp.readyState === 4 && xmlhttp.status === 201) {
                console.log("Created new Room");

                var obj = JSON.parse(xmlhttp.responseText);
                openRoomId.text = obj.id

                roomWaitView.visible   = true
                roomView.visible   = false
                roomTimer.running = true
            }
        }
        xmlhttp.open("POST", url, true);
        xmlhttp.setRequestHeader("Content-type", "application/json");
        xmlhttp.send(data);
    }

    function deleteRoom(id){
        var xmlhttp = new XMLHttpRequest();
        var url = "http://adambarca123.pythonanywhere.com/game/"+ id +"/";

        xmlhttp.onreadystatechange=function() {
            if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {
                console.log("Deleted Room");
                getRooms()
                roomWaitView.visible   = false
                roomTimer.running = false
            }
        }
        xmlhttp.open("DELETE", url, true);
        xmlhttp.send();
    }

    function checkStart(id){
        var xmlhttp = new XMLHttpRequest();
        var url = "http://adambarca123.pythonanywhere.com/game/"+id+"/";

        xmlhttp.onreadystatechange=function() {
            if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {
                var obj = JSON.parse(xmlhttp.responseText);
                if (obj.state === "start"){
                    roomWaitView.visible   = false
                    gameView.visible   = true
                    var board = obj.chessboard
                    printBoard(board)
                    player1 = obj.player1
                    player2 = obj.player2
                    onTurn = obj.onTurn
                    gameId = obj.id
                    figureColor = "w"
                    isOnline = true
                    roomTimer.running = false
                    gameTimer.running = true

                    colorInfo.visible = true
                    colorInfoText.visible = true
                    surrender.visible = true
                    askDraw.text = "Ask draw"
                }
            }
        }
        xmlhttp.open("GET", url, true);
        xmlhttp.send();
    }

    function startGame(id){
        var xmlhttp = new XMLHttpRequest();
        var url = "http://adambarca123.pythonanywhere.com/game/"+ id +"/";
        var data = JSON.stringify({"name": userName});

        xmlhttp.onreadystatechange=function() {
            if (xmlhttp.readyState === 4 && xmlhttp.status === 201) {
                console.log("Started game");
                var obj = JSON.parse(xmlhttp.responseText);
                roomView.visible   = false
                gameView.visible   = true
                var board = obj.chessboard
                printBoard(board)
                player1 = obj.player1
                player2 = obj.player2
                onTurn = obj.onTurn
                gameId = obj.id
                figureColor = "b"
                isOnline = true
                gameTimer.running = true

                colorInfo.visible = true
                colorInfoText.visible = true
                surrender.visible = true
                askDraw.text = "Ask draw"
            }
        }
        xmlhttp.open("POST", url, true);
        xmlhttp.setRequestHeader("Content-type", "application/json");
        xmlhttp.send(data);
    }

    function checkGame(){
        var xmlhttp = new XMLHttpRequest();
        var url = "http://adambarca123.pythonanywhere.com/game/"+gameId+"/";

        xmlhttp.onreadystatechange=function() {
            if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {
                var obj = JSON.parse(xmlhttp.responseText);
                if(obj.state ==="start"){

                    player1 = obj.player1
                    player2 = obj.player2
                    onTurn = obj.onTurn

                    console.log(onTurn, obj.state, (!onTurn && player1 === userName)||(onTurn && player2 === userName))

                    if((!onTurn && player1 === userName)||(onTurn && player2 === userName)){
                        printBoard(obj.chessboard)
                    }
                }
                else{

                    setGameOverState(obj.state)
                    gameOverView.visible = true
                    gameView.visible   = false
                    gameTimer.running = false
                }
            }
        }
        xmlhttp.open("GET", url, true);
        xmlhttp.send();
    }

    function click(x){
        var xmlhttp = new XMLHttpRequest();
        var url = "http://adambarca123.pythonanywhere.com/game/"+ gameId +"/click/";
        var data = JSON.stringify({"tah": x});

        xmlhttp.onreadystatechange=function() {
            if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {
                console.log("clicked "+x);
                var obj = JSON.parse(xmlhttp.responseText);
                printBoard(obj.response)
                checkGame()
            }
        }
        xmlhttp.open("POST", url, true);
        xmlhttp.setRequestHeader("Content-type", "application/json");
        xmlhttp.send(data);
    }

    function setGameOverState(x){
        if(x==="remiza"){
            gameOverState.text = "It is draw!!!"
        }
        if(x==="vyhral 1"){
            gameOverState.text = player1+" won!!!"
        }
        if(x==="vyhral 2"){
            gameOverState.text = player2+" won!!!"
        }
    }

    function setState(x){
        var xmlhttp = new XMLHttpRequest();
        var url = "http://adambarca123.pythonanywhere.com/game/"+ gameId +"/finish/";
        var data = JSON.stringify({"state": x});

        xmlhttp.onreadystatechange=function() {
            if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {
                console.log("State seted");
                var obj = JSON.parse(xmlhttp.responseText);
                setGameOverState(obj.state)
                gameOverView.visible = true
                gameView.visible   = false
                gameTimer.running = false
            }
        }
        xmlhttp.open("POST", url, true);
        xmlhttp.setRequestHeader("Content-type", "application/json");
        xmlhttp.send(data);
    }

    Item {
        /* use id for access */
        id: menuView
        width: 800
        height: 600
        visible: true
        /* visible: true */


        Button {
            id: onePlayer
            x: 143
            y: 245
            width: 200
            height: 70
            font.pointSize: 30
            text: qsTr("1 Player")
            /* just change `visible` property by click */
            onClicked: {
                menuView.visible = false
                gameView.visible = true
                var board = "00400040004000404000400040004000004000400040004040404040404040404040404040404040401040104010401010401040104010404010401040104010"
                printBoard(board)
                player1 = userName
                player2 = "Computer"
                onTurn = false

                colorInfo.visible = true
                colorInfoText.visible = true
                surrender.visible = false
                askDraw.text = "Leave"
            }
        }

        Button {
            id: twoPlayers
            x: 464
            y: 245

            width: 200
            height: 70
            font.pointSize: 30
            text: qsTr("2 Players")

            onClicked: {
                menuView.visible   = false
                gameView.visible   = true
                var board = "00400040004000404000400040004000004000400040004040404040404040404040404040404040401040104010401010401040104010404010401040104010"
                printBoard(board)
                player1 = "Player1"
                player2 = "Player2"
                onTurn = false

                colorInfo.visible = false
                colorInfoText.visible = false
                surrender.visible = false
                askDraw.text = "Leave"
            }
        }

        Button {
            id: online
            x: 143
            y: 376
            width: 200
            height: 70
            font.pointSize: 30
            text: qsTr("Online")
            /* just change `visible` property by click */
            onClicked: {
                menuView.visible = false
                getRooms()
            }
        }

        Button {
            id: options
            x: 464
            y: 376

            width: 200
            height: 70
            font.pointSize: 30
            text: qsTr("Options")

            onClicked: {
                menuView.visible   = false
                optionsView.visible   = true
            }
        }




        Text {
            anchors.centerIn: parent
            text: "Checkers"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.NoWrap
            font.pointSize: 60
            minimumPixelSize: 34
            minimumPointSize: 16
            renderType: Text.QtRendering
            textFormat: Text.PlainText
            anchors.verticalCenterOffset: -160
            anchors.horizontalCenterOffset: 0
        }


    }






    Item {
        id: gameView
        x: 0
        y: 0
        /* invisible */
        visible: false
        width: 800
        height: 600



        Text {
            id: text1
            x: 548
            y: 178
            width: 200
            height: 40
            text: player1 //qsTr("Player1")
            font.pixelSize: 30
            horizontalAlignment: Text.AlignHCenter
        }


        Text {
            id: text3
            x: 548
            y: 264
            width: 200
            height: 40
            text: player2 //qsTr("Player2")
            font.pixelSize: 30
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        Button {
            id: askDraw
            x: 555
            y: 368
            width: 200
            height: 70
            text: "Ask draw"
            font.pointSize: 30

            onClicked: {

                if (isOnline){
                    setState(0)
                }
                else{
                    menuView.visible   = true
                    gameView.visible   = false
                }

                isOnline = false
            }
        }

        Button {
            id: surrender
            x: 555
            y: 471
            text: qsTr("Surrender")
            width: 200
            height: 70
            font.pointSize: 30

            onClicked: {

                if (isOnline){
                      if(userName === player1){
                          setState(2)
                      }
                      else{
                          setState(1)
                      }
                      isOnline = false
                }
                else{
                    menuView.visible     = true
                    gameView.visible   = false
                }
            }
        }

        Rectangle {
            id: boardWhite
            x: 100
            y: 100
            width: 400
            height: 400
            color: whiteColor
            radius: 0
            border.width: 0

            Rectangle {
                id: a1
                x: 0
                y: 350
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"a1")
                }
                Rectangle {
                    id: a1Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    radius: 15
                    color: "#ffffff"
                    border.width: 0
                }
            }

            Rectangle {
                id: c1
                x: 100
                y: 350
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"c1")
                }
                Rectangle {
                    id: c1Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: e1
                x: 200
                y: 350
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"e1")
                }
                Rectangle {
                    id: e1Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: g1
                x: 300
                y: 350
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"g1")
                }
                Rectangle {
                    id: g1Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: b2
                x: 50
                y: 300
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"b2")
                }
                Rectangle {
                    id: b2Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: d2
                x: 150
                y: 300
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"d2")
                }
                Rectangle {
                    id: d2Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: f2
                x: 250
                y: 300
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"f2")
                }
                Rectangle {
                    id: f2Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: h2
                x: 350
                y: 300
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"h2")
                }
                Rectangle {
                    id: h2Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: a3
                x: 0
                y: 250
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"a3")
                }
                Rectangle {
                    id: a3Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: c3
                x: 100
                y: 250
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"c3")
                }

                Rectangle {
                    id: c3Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: e3
                x: 200
                y: 250
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"e3")
                }
                Rectangle {
                    id: e3Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: g3
                x: 300
                y: 250
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"g3")
                }
                Rectangle {
                    id: g3Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: b4
                x: 50
                y: 200
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"b4")
                }
                Rectangle {
                    id: b4Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: d4
                x: 150
                y: 200
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"d4")
                }
                Rectangle {
                    id: d4Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: f4
                x: 250
                y: 200
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"f4")
                }
                Rectangle {
                    id: f4Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: h4
                x: 350
                y: 200
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"h4")
                }
                Rectangle {
                    id: h4Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: a5
                x: 0
                y: 150
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"a5")
                }
                Rectangle {
                    id: a5Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: c5
                x: 100
                y: 150
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"c5")
                }
                Rectangle {
                    id: c5Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: e5
                x: 200
                y: 150
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"e5")
                }
                Rectangle {
                    id: e5Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: g5
                x: 300
                y: 150
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"g5")
                }
                Rectangle {
                    id: g5Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: b6
                x: 50
                y: 100
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"b6")
                }
                Rectangle {
                    id: b6Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: d6
                x: 150
                y: 100
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"d6")
                }
                Rectangle {
                    id: d6Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: f6
                x: 250
                y: 100
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"f6")
                }
                Rectangle {
                    id: f6Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: h6
                x: 350
                y: 100
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"h6")
                }
                Rectangle {
                    id: h6Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: a7
                x: 0
                y: 50
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"a7")
                }
                Rectangle {
                    id: a7Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: c7
                x: 100
                y: 50
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"c7")
                }
                Rectangle {
                    id: c7Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: e7
                x: 200
                y: 50
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"e7")
                }
                Rectangle {
                    id: e7Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: g7
                x: 300
                y: 50
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"g7")
                }
                Rectangle {
                    id: g7Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: b8
                x: 50
                y: 0
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"b8")
                }
                Rectangle {
                    id: b8Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.color: "#000000"
                    border.width: 0
                }
            }

            Rectangle {
                id: d8
                x: 150
                y: 0
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"d8")
                }
                Rectangle {
                    id: d8Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: f8
                x: 250
                y: 0
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"f8")
                }
                Rectangle {
                    id: f8Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }

            Rectangle {
                id: h8
                x: 350
                y: 0
                width: 50
                height: 50
                color: blackColor
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    onClicked: click(figureColor+"h8")
                }
                Rectangle {
                    id: h8Figure
                    x: 10
                    y: 10
                    width: 30
                    height: 30
                    color: "#ffffff"
                    radius: 15
                    border.width: 0
                }
            }


        }

        Text {
            id: text2
            x: 634
            y: 224
            text: qsTr("vs")
            font.pixelSize: 30
        }

        Rectangle {
            id: rectangle
            x: 598
            y: 142
            width: 100
            height: 30
            color: "#3bde4f"
            visible: !onTurn

            Text {
                id: text7
                x: 0
                y: 0
                width: 100
                height: 30
                text: qsTr("On turn")
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                minimumPixelSize: 30
            }
        }

        Rectangle {
            id: rectangle1
            x: 598
            y: 305
            width: 100
            height: 30
            color: "#3bde4f"
            visible: onTurn

            Text {
                id: text8
                x: 0
                y: 0
                width: 100
                height: 30
                text: qsTr("On turn")
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                minimumPixelSize: 30
            }
        }

        Text {
            id: colorInfoText
            x: 584
            y: 100
            width: 100
            height: 30
            text: qsTr("Your color:")
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
        }

        Rectangle {
            id: colorInfo
            x: 690
            y: 100
            width: 30
            height: 30
            color: player1 == userName ? whiteFigureColor : blackFigureColor
            radius: 15
        }

        Timer {
            id: gameTimer
            interval: 1000
            running: false
            repeat: true
            onTriggered: checkGame()
        }
    }
    Item {
        id: roomView
        x: 0
        y: 0
        /* invisible */
        visible: false
        width: 800
        height: 600

        Text {
            id: text4
            x: 200
            y: 52
            text: qsTr("Choose a room")
            font.pixelSize: 60
        }

        Button {
            id: button2
            x: 285
            y: 150
            width: 230
            height: 50
            text: qsTr("Create new room")
            font.pointSize: 20
            onClicked: {
                addRoom()
            }
        }

        Button {
            id: roomBackToMenu
            x: 340
            y: 480
            width: 120
            height: 70
            text: qsTr("Back")
            font.pointSize: 30

            onClicked: {
                menuView.visible   = true
                roomView.visible   = false
            }
        }
        ListModel{
            id: roomsModel
            ListElement{
                roomId: 1
                player: "Risanko"
            }
        }

        ScrollView {
            id: scrollView
            x: 225
            y: 280
            width: 350
            height: 120
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

            ListView {
                id: roomsListView
                visible: true
                anchors.fill: parent
                model: roomsModel
                delegate: Rectangle {
                    id: roomItem
                    width: 350
                    height: 60
                    color: "#abe8ff"

                    Text {
                        id: roomName
                        x: 46
                        y: 8
                        text: "Room " + roomId
                    }
                    Text {
                        id: creator
                        x: 27
                        y: 33
                        text: "Creator: "+ player
                    }
                    Button{
                        x: 220
                        y: 15
                        width: 100
                        height: 30
                        text: "Join and play"

                        onClicked: {
                            startGame(roomId)
                        }
                    }

                }
            }

        }
    }
    Item {
        id: roomWaitView
        x: 0
        y: 0
        /* invisible */
        visible: false
        width: 800
        height: 600

        Text {
            id: waiting
            x: 141
            y: 227
            text: qsTr("Waiting for an another player")
            font.pixelSize: 40
        }

        Button {
            id: backToRoom
            x: 340
            y: 431
            width: 120
            height: 70
            text: qsTr("Back")
            font.pointSize: 30

            onClicked: {
                deleteRoom(openRoomId.text)
            }
        }

        Text {
            id: openRoomId
            x: 449
            y: 112
            width: 133
            height: 73
            text: "ID"
            font.pixelSize: 60
        }

        Text {
            id: text9
            x: 262
            y: 112
            text: qsTr("Room")
            font.pixelSize: 60
            minimumPixelSize: 60
        }

        Timer {
            id: roomTimer
            interval: 1000
            running: false
            repeat: true
            onTriggered: checkStart(openRoomId.text)
        }
    }
    Item {
        id: optionsView
        x: 0
        y: 0
        /* invisible */
        visible: false
        width: 800
        height: 600

        Text {
            id: chooseRoom
            x: 294
            y: 56
            text: qsTr("Options")
            font.pixelSize: 60
        }

        Button {
            id: optionsBackToMenu
            x: 340
            y: 470
            width: 120
            height: 70
            text: qsTr("Back")
            font.pointSize: 30

            onClicked: {
                menuView.visible   = true
                optionsView.visible   = false
                switch(comboBox.currentIndex) {
                    case 1:
                        blackColor = "#474046";
                        whiteColor = "#d53838";
                        blackFigureColor = "#000000";
                        whiteFigureColor = "#e11515";
                    break;
                    case 2:
                        blackColor = "#9c6008";
                        whiteColor = "#f9f782";
                        blackFigureColor = "#564a00";
                        whiteFigureColor = "#f7ff00";
                    break;
                    case 3:
                        blackColor = "#1d8f10";
                        whiteColor = "#f9f782";
                        blackFigureColor = "#0d5f03";
                        whiteFigureColor = "#f7ff00";
                    break;
                    default:
                        blackColor = "#474046";
                        whiteColor = "#ffffff";
                        blackFigureColor = "#000000";
                        whiteFigureColor = "#e0e0e0";
                }
            }
        }

        Text {
            id: text5
            x: 270
            y: 170
            text: qsTr("Choose board color")
            font.pixelSize: 30
        }

        Text {
            id: text6
            x: 276
            y: 320
            text: qsTr("Choose your name")
            font.pixelSize: 30
        }

        TextInput {
            id: textInput
            x: 275
            y: 380
            width: 250
            height: 40
            color: "#000000"
            text: qsTr("Player1")
            font.pixelSize: 30
            horizontalAlignment: Text.AlignHCenter
        }

        ComboBox {
            id: comboBox
            x: 300
            y: 230
            width: 200
            height: 40
            currentIndex: 0
            font.pointSize: 18

            model: ["Black, White", "Black, Red", "Brown, Yellow", "Green, Yellow"]
        }
    }

    Item {
        id: gameOverView
        x: 0
        y: 0
        /* invisible */
        visible: false
        width: 800
        height: 600

        Text {
            id: gameOverState
            x: 0
            y: 197
            width: 800
            height: 80
            text: "Player1 won!!!!"
            font.pixelSize: 70
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Button {
            id: backToMenu
            x: 340
            y: 431
            width: 120
            height: 70
            text: qsTr("Back")
            font.pointSize: 30

            onClicked: {
                menuView.visible   = true
                gameOverView.visible   = false
            }
        }


    }
}


/*##^##
Designer {
    D{i:1;invisible:true}D{i:47;invisible:true}D{i:46;invisible:true}D{i:64;invisible:true}
D{i:77;invisible:true}D{i:78;invisible:true}D{i:84;invisible:true}D{i:109;invisible:true}
D{i:110;invisible:true}D{i:116;invisible:true}D{i:117;invisible:true}
}
##^##*/
