import xml.etree.ElementTree as ET



STATE_STYLE = "html=1;align=center;"
TRANS_STYLE = "edgeStyle=none;html=1;endArrow=open;"


def main():
    tree = ET.parse('fsm_led.xml')
    root = tree.getroot()

    states=[]
    transitions=[]
    for type_tag in root.findall('diagram/mxGraphModel/root/mxCell'):
        style = type_tag.get('style')
        if style != None:
            if STATE_STYLE in style:
                states.append(type_tag)
            if TRANS_STYLE in style:
                transitions.append(type_tag)

    print('States:')
    for item in states:
        print(item.get('value'))

    print('\nTransitions:')
    for item in transitions:
        print(item.get('value'))



if __name__ == "__main__":
    main()