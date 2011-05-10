import Qt 4.7

Item
{
	id: container
	property alias cellColor: rectangle.color
	signal clicked(color cellColor)
	width: 40
	height: 25

	Rectangle
	{
		id: rectangle
		border.color: "White"
		anchors.fill: parent
	}
	
	MouseArea
	{
		anchors.fill: parent
		onClicked: container.clicked(container.cellColor)
	}
	
}
