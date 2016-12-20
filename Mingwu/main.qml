import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("MingWu")

Rectangle{
    color:"red"
    anchors.centerIn: parent
    width: 200
    height: 200

    Text {
        id: name
        text: qsTr("Info")

        anchors.centerIn: parent
    }
}
Row{
    Button{
        text: qsTr("Load")
        onClicked: name.text = inter.loadFromFile("main.qml")
    }
}
}
