import QtQuick 2.11

Item {
    id: window
    visible: true
    width: 1280
    height: 480

    Loader {
        id: mainclusterloader
        anchors.fill: parent
    }

    Component.onCompleted: {
        mainclusterloader.setSource("qrc://qml/MainCluster.qml")
    }


}
