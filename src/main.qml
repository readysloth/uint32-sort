import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4 as OldCtrl
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.12
import com.sort.controller 0.1

Window{
    height: 340
    FileDialog {
        id: fileDialog_for_sort
        title: "Выберите файл для сортировки"
        selectedNameFilter: "All files (*)"
        Component.onCompleted: visible = true
        onAccepted: {
            fileDialog_for_save.open()
            libController.addFile(fileDialog_for_sort.fileUrl, fileDialog_for_save.fileUrl)
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
        onClicked: fileDialog_for_sort.open()
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

        RadioButton {
            id: ascOrder
            text: qsTr("По убыванию")
            OldCtrl.exclusiveGroup: exOrder
        }

        RadioButton {
            id: descOrder
            text: qsTr("По возрастанию")
            OldCtrl.exclusiveGroup: exOrder
        }
    }

    Text {
        id: element
        x: 29
        y: 66
        width: 582
        height: 25
        text: qsTr("Выбран файл ")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 14
    }

    Text {
        id: element1
        x: 119
        y: 16
        text: qsTr("Сортировка uint32_t чисел")
        font.pixelSize: 30
    }

    Text {
        id: element2
        x: 29
        y: 97
        width: 582
        height: 25
        text: qsTr("Результат будет сохранен в ")
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
        value: 0.5
    }

}
