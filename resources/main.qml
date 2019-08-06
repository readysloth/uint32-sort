import QtQuick 2.12
import QtQml 2.13
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
            if(fileDialog_for_load.fileUrl.toString() === ""){
                emptyFilename.open()
            }
            else{
                var loadPath = fileDialog_for_load.fileUrl.toString();
                loadPath = loadPath.replace(/^(file:\/{2})/,"");

                libController.fileToSort = loadPath

                fileDialog_for_save.open()
            }

        }
    }
    FileDialog {
        id: fileDialog_for_save
        title: "Сохранить отсортированный файл"
        selectFolder: true
        selectedNameFilter: "All files (*)"
        Component.onCompleted: visible = true
        onAccepted: {
            if(fileDialog_for_save.fileUrl.toString() === ""){
                emptyFilename.open()
            }
            if(fileDialog_for_load.fileUrl.toString() === fileDialog_for_save.fileUrl.toString()){
                fileOverwrite.open()
            }
            else{
                var savePath = fileDialog_for_save.fileUrl.toString();
                savePath = savePath.replace(/^(file:\/{2})/,"") + "/";
                var filename = libController.fileToSort.match(/([^/]+?)$/)[1]
                libController.setSaveFile(savePath, filename)

                libController.createFileManager()
            }
        }
    }

    LibController {
        id: libController

        onHandleGenFail: {
            generic_fail.open()
        }
        onHandleMapFail: {
            fileMap_fail.open()
        }
        onHandleLenFail: {
            fileLen_fail.open()
        }
        onHandleOpenFail: {
            fileOpen_fail.open()
        }
        onHandleNotReady: {
            fileNotReady.open()
        }
        onHandleReady: {
            fileReady.open()
        }
    }

    Button {
        id: choose_file
        x: 29
        y: 244
        text: qsTr("Выбрать файл")
        onClicked: {
            progressBar.value = 0
            fileDialog_for_load.open()
        }
    }

    Button {
        id: sort_file
        x: 511
        y: 244
        text: qsTr("Сортировать")
        onClicked: {
            progressBar.value = 0
            updateProgress.start()
            libController.sortFile()
        }
    }

    Timer {
        id: updateProgress
        interval: 1000;
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

    Item {
        id: errorReporter
        visible: false

        //------------Сообщения для пользователя------------\\
        MessageDialog {
            id: fileNotReady
            visible: false
            icon: StandardIcon.Warning
            title: qsTr("Уведомление")
            text: qsTr("Пожалуйста, дождитесь окончания процесса сортировки.")
        }

        MessageDialog {
            id: fileReady
            visible: false
            icon: StandardIcon.Information
            title: qsTr("Ура!")
            text: qsTr("Сортировка закончена.")
        }

        MessageDialog {
            id: fileOverwrite
            visible: false
            icon: StandardIcon.Warning
            title: qsTr("Нежелательное действие")
            text: qsTr("Вы выбрали в качестве файла для сортировки и сохранения один и тот же файл. " +
                   "Это приведет к тому, что исходный файл станет пустым. " +
                   "Пожалуйста, выберите другой файл для сохранения или закройте программу")
            onAccepted: {
                fileDialog_for_save.open()
            }
        }

        MessageDialog {
            id: emptyFilename
            visible: false
            icon: StandardIcon.Warning
            title: qsTr("Нежелательное действие")
            text: qsTr("Каким-то образом одно из файловых имен не было предоставлено программе. " +
                        "Пожалуйста, выберите файлы еще раз или закройте программу")
            onAccepted: {
                fileDialog_for_load.open()
            }
        }

        MessageDialog {
            id: generic_fail
            visible: false
            icon: StandardIcon.Critical
            title: qsTr("Системная ошибка")
            text: qsTr("Произошла неопознанная ошибка при работе программы. " +
                   "Выберите другой файл, подождите, либо закройте программу.")
            onAccepted: {  }
        }

        MessageDialog {
            id: fileMap_fail
            visible: false
            icon: StandardIcon.Critical
            title: qsTr("Системная ошибка")
            text: qsTr("Файл не может быть отображен в память. " +
                   "Выберите другой файл, подождите, либо закройте программу. ")
            onAccepted: {
                fileDialog_for_load.open()
            }
        }

        MessageDialog {
            id: fileLen_fail
            visible: false
            icon: StandardIcon.Critical
            title: qsTr("Системная ошибка")
            text: qsTr("Файл не может быть обработан, так как содержит число неправильного размера (размер не кратен размеру uint32_t). " +
                   "Выберите другой файл, подождите, либо закройте программу.")
            onAccepted: {
                fileDialog_for_load.open()
            }
        }

        MessageDialog {
            id: fileOpen_fail
            visible: false
            icon: StandardIcon.Critical
            title: qsTr("Системная ошибка")
            text: qsTr("Файл не может быть обработан, так как не может быть открыт. " +
                   "Выберите другой файл, измените привелегии, либо закройте программу.")
            onAccepted: {
                fileDialog_for_load.open()
            }
        }

        MessageDialog {
            id: fileCopy_fail
            visible: false
            icon: StandardIcon.Critical
            title: qsTr("Системная ошибка")
            text: qsTr("Файл не может быть обработан, так как произошла ошибка при копировании. " +
                   "Выберите другой файл, подождите, либо закройте программу.")
            onAccepted: {
                fileDialog_for_load.open()
            }
        }

    }

}
