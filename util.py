import os

def getDict(file_name):
    """
    Checks whether a file's extension is ".xml" or ".json", and parses the
    file (depending on the extension) as XML or JSON.
    
    Args:
        file_name (string): File name
    
    Returns:
        Python dict filled with info from file. Hierarchy is faithfully 
        reproduced.
    """
    filename, extension = os.path.splitext(file_name)
    if extension == ".xml":
        try:
            import xmltodict
        except ImportError:
            print("xmltodict module not installed in Python")
            exit(1)
        with open(file_name) as fd:
            return xmltodict.parse(fd.read())
    elif extension == ".json":
        import json
        with open(file_name) as fd:
            return json.load(fd)
    else:
        print("Unhandled exetension for " + file_name)
        return None