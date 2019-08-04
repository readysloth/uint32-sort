import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4 as OldCtrl
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.12
import sorting 1.0

Window{
    visible: true
    width: 640
    height: 340

    Text {
        id: title
        x: 119
        y: 16
        text: qsTr("Сортировка uint32_t чисел")
        font.pixelSize: 30
    }

    FileDialog {
        id: fileDialog_for_load
        title: "Выберите файл для сортировки"
        selectedNameFilter: "All files (*)"
        selectExisting: true
        Component.onCompleted: visible = true
        onAccepted: {
            var loadPath = fileDialog_for_load.fileUrl.toString();
            loadPath = loadPath.replace(/^(file:\/{2})/,"");

            libController.setFromFile(loadPath)

            fileDialog_for_save.open()

        }
    }
    FileDialog {
        id: fileDialog_for_save
        title: "Сохранить отсортированный файл"
        selectExisting: false
        selectedNameFilter: "All files (*)"
        Component.onCompleted: visible = true
        onAccepted: {
            if(fileDialog_for_load.fileUrl.toString() === fileDialog_for_save.fileUrl.toString())
                fileOverwrite.open()

            var savePath = fileDialog_for_save.fileUrl.toString();
            savePath = savePath.replace(/^(file:\/{2})/,"");

            libController.setToFile(savePath)

            libController.passToFileManager()
        }
    }

    LibController { id: libController }

    Button {
        id: choose_file
        x: 29
        y: 244
        text: qsTr("Выберите файл")
        onClicked: fileDialog_for_load.open()
    }

    Button {
        id: sort_file
        x: 511
        y: 244
        text: qsTr("Сотировать")
        onClicked: {
            progressBar.value = 0
            updateProgress.start()
            libController.sortFile()
        }
    }

    Timer {
        id: updateProgress
        interval: 20;
        repeat: true
        onTriggered: {
            progressBar.value = libController.progress
        }
    }

    ColumnLayout {
        id: orderLayout
        x: 352
        y: 214
        width: 153
        height: 100
        OldCtrl.ExclusiveGroup{ id: exOrder }

        OldCtrl.RadioButton {
            id: descOrder
            text: qsTr("По убыванию")
            exclusiveGroup: exOrder
            onClicked: {
                libController.setOrderDesc()
            }
        }

        OldCtrl.RadioButton {
            id: ascOrder
            checked: true
            text: qsTr("По возрастанию")
            exclusiveGroup: exOrder
            onClicked: {
                libController.setOrderAsc()
            }
        }
    }

    Text {
        id: chosen_file_txt
        x: 29
        y: 66
        width: 582
        height: 25
        text: qsTr("Выбран файл ") + fileDialog_for_load.fileUrl
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 14
    }


    Text {
        id: file_save_txt
        x: 29
        y: 97
        width: 582
        height: 25
        text: qsTr("Результат будет сохранен в ") + fileDialog_for_save.fileUrl
        font.pixelSize: 14
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
    }

    ProgressBar {
        id: progressBar
        x: 29
        y: 157
        width: 582
        height: 27
        value: 0
    }


}
