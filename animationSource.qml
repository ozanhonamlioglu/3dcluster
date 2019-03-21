import QtQuick 2.0

Item {
    id: animationSource
    property real kmh: 0

    SequentialAnimation {

        ParallelAnimation {

            NumberAnimation {
                target: animationSource
                property: "kmh"
                duration: 3000
                easing.type: Easing.InOutQuad
            }

        }

    }

}
