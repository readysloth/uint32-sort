import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4 as OldCtrl
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.12
import sorting 1.0

Window{
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
        Component.onCompleted: visible = true
        onAccepted: {
            fileDialog_for_save.open()
            libController.addFile(fileDialog_for_load.fileUrl, fileDialog_for_save.fileUrl)
        }
    }
    FileDialog {
        id: fileDialog_for_save
        title: "Сохранить отсортированный файл"
        selectExisting: false
        selectedNameFilter: "All files (*)"
        Component.onCompleted: visible = true
        onAccepted: {
            var loadPath = fileDialog_for_load.fileUrl.toString();
            loadPath = loadPath.replace(/^(file:\/{2})/,"");

            var savePath = fileDialog_for_save.fileUrl.toString();
            savePath = savePath.replace(/^(file:\/{2})/,"");

            console.log("Save Path:" + savePath)
            libController.addFile()(loadPath, savePath)
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
        onClicked: libController.sortFile()
    }

    ColumnLayout {
        id: orderLayout
        x: 352
        y: 214
        width: 153
        height: 100
        OldCtrl.ExclusiveGroup{ id: exOrder }

        OldCtrl.RadioButton {
            id: ascOrder
            text: qsTr("По убыванию")
            exclusiveGroup: exOrder
        }

        OldCtrl.RadioButton {
            id: descOrder
            text: qsTr("По возрастанию")
            exclusiveGroup: exOrder
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
