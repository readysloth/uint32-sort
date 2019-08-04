import QtQuick 2.0
import QtQuick.Dialogs 1.2

Item {
    id: errorReporter
    //------------Сообщения для пользователя------------\\
    MessageDialog {
        id: fileOverwrite
        visible: false
        icon: StandardIcon.Warning
        title: qsTr("Нежелательное действие")
        text: qsTr("Вы выбрали в качестве файла для сортировки и сохранения один и тот же файл." +
                   "Это приведет к тому, что исходный файл станет пустым." +
                   "Пожалуйста, выберите другой файл для сохранения или закройте программу")
        onAccepted: {
            fileDialog_for_save.open()
        }
    }

    MessageDialog {
        id: fileMap_fail
        visible: false
        icon: StandardIcon.Critical
        title: qsTr("Системная ошибка")
        text: qsTr("Файл не может быть отображен в память." +
                   "Выберите другой файл, подождите, либо закройте программу.")
        onAccepted: {
            fileDialog_for_load.open()
        }
    }

    MessageDialog {
        id: fileLen_fail
        visible: false
        icon: StandardIcon.Critical
        title: qsTr("Системная ошибка")
        text: qsTr("Файл не может быть обработан, так как содержит число неправильного размера (размер не кратен размеру uint32_t)." +
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
        text: qsTr("Файл не может быть обработан, так как не может быть открыт." +
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
        text: qsTr("Файл не может быть обработан, так как произошла ошибка при копировании." +
                   "Выберите другой файл, подождите, либо закройте программу.")
        onAccepted: {
            fileDialog_for_load.open()
        }
    }

}
