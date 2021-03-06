import QtQuick 2.12
import QtQuick.Controls 2.12
import QtMultimedia 5.0
import "./" as SokobanItems

Button
{
    property color downColor: "gray"
    property color bnColor: "transparent"
    property var audioFileOnClicked: "qrc:/sounds/sounds/sound_bn_menu_clicked.mp3"
    property bool animationActive: false
    property int fontSize: 17
    signal clickedPlaySound

    id: root
    implicitWidth: 30
    implicitHeight: 30

    contentItem: SokobanItems.Text
    {
        id: text
        text: root.text
        font.pointSize: fontSize
        color: root.down ? downColor : sourceColor
        anchors.centerIn: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        Component
        {
            id: textAnimation
            ParallelAnimation
            {
                property int duration: 300

                id: parallelAnimation
                running: true
                SequentialAnimation
                {
                    loops: Animation.Infinite
                    PropertyAnimation {
                        target: text; properties: "font.pointSize"; to: text.font.pointSize - 4; duration: parallelAnimation.duration
                    }
                    PropertyAnimation {
                        target: text; properties: "font.pointSize"; to: text.font.pointSize; duration: parallelAnimation.duration
                    }
                }
            }
        }
        Loader
        {
            id: loaderBnAnimation
            sourceComponent: textAnimation
            active: root.animationActive
            onActiveChanged: { text.font.pointSize = fontSize }
        }
    }

    background: SokobanItems.Rectangle { id: bnBackground; color: bnColor }

    Audio { id: soundClicked; source: audioFileOnClicked }
    onClicked: soundClicked.play()
}
