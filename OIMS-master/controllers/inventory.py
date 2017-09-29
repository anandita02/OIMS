@auth.requires_membership("Inventory Manager")
def index():
    return "Create Location"

@auth.requires_membership("Inventory Manager")
def createCategory():
    return "Create Location"

@auth.requires_membership("Inventory Manager")
def viewCategories():
    return "View Locations"

@auth.requires_membership("Inventory Manager")
def editCategories():
    return "Edit Locations"

@auth.requires_membership("Inventory Manager")
def createItem():
    return "Create Location"

@auth.requires_membership("Inventory Manager")
def viewItems():
    return "View Locations"

@auth.requires_membership("Inventory Manager")
def editItems():
    return "Edit Locations"
