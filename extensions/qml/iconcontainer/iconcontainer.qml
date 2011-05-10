import Qt 4.7
import "component"
import "component/images"
import Qt.labs.folderlistmodel 1.0
import IconLoader 1.0

Rectangle {

    width: 360
    height: 360
    color: "#070606"
    opacity: 0.8
    GridView{
        x: 0
        y: 30
        width: 360
        height: 330
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 30
        anchors.fill: parent
        Grid{
        id: grid
        columns:  5
        spacing: 10
        rows: 4
        Component
        {
            id:fileDelegate
            Icon{txt: fileName}
        }
        }
        model: flm
        delegate: fileDelegate
    }

    FolderListModel
    {
        id: flm
        folder: "."
        nameFilters: ["*"]
    }

    Image {
        id: image1
        x: 8
        y: 5
        width: 25
        height: 23
        source: "component/images/Back.png"
    }
    function goUp()
    {
        flm.folder = flm.parentFolder.toString()
    }
    function goInto(to)
    {
	var cpath = flm.folder.toString();
	var npath = cpath + "/" + to.toString();
	flm.folder = npath;
	if (!flm.isFolder())
		flm.folder = cpath;
    }

    MouseArea {
        id: mouse_area1
        x: 8
        y: 5
        width: 25
        height: 23
        z: 1
        onClicked: goUp()

    }


}
