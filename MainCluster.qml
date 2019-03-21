import QtQuick 2.11
import QtQuick.Window 2.11
import QtStudio3D 2.2
import QtPositioning 5.8

Item {
    id: cluster

    AnimationValues {
        id: animvalues
    }

    function speedTransition(speed) {
        var adaptedSpeed = -136 + speed
        return adaptedSpeed
    }

    Studio3D {
        id: s3d
        focus: true
        anchors.margins: 0
        anchors.fill: parent

        Presentation {
            id: s3dpress
            source: "qrc:/Cluster/SampleProject.uia"

            DataInput {
                id: slideInput
                name: "slide"
            }

            DataInput {
                // animation variables
                property real kmh: animvalues.didAnimationFinished ? speedTransition(canObject.retData.speed) : animvalues.kmh

                id: speedNeedleInput
                name: "speedNeedle"
                value: Qt.vector3d(0, kmh,0)

                Behavior on kmh {
                    enabled: animvalues.didAnimationFinished
                    NumberAnimation {
                        duration: 500
                    }
                }

            }

            SceneElement {
                id: scene
                elementPath: "Scene"
                currentSlideName: "Front"
            }

        }

        onRunningChanged: {
            // do some
        }

    }


    MouseArea {
        anchors.fill: parent
        onClicked: {
            var slidename = scene.currentSlideName
            if(slidename === "Front" || slidename === "InitialState") {
                slideInput.setValue("Angle")
            } else {
                slideInput.setValue("InitialState")
            }
        }
    }


}
