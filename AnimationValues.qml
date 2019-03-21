import QtQuick 2.0

Item {
    id: animationSource
    property real kmh: 0
    property bool didAnimationFinished: false

    SequentialAnimation {
        id: mainAnim
        running: true
        loops: 1
        onRunningChanged: {
            if(!mainAnim.running){
                didAnimationFinished=true
            }
        }

        NumberAnimation {
            target: animationSource
            property: "kmh"
            duration: 1000
            from: -136
            to: 120
        }

        NumberAnimation {
            target: animationSource
            property: "kmh"
            duration: 1000
            from: 120
            to: -136
        }

    }

}
