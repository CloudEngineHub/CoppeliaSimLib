#include "app.h"
#include "moduleMenuItemContainer.h"
#include "global.h"

CModuleMenuItemContainer::CModuleMenuItemContainer()
{
    _nextSmallItemCommandID=ADDITIONAL_TOOL_MENU_ITEM_START_CMD;
    _menuHandle=nullptr;
}

CModuleMenuItemContainer::~CModuleMenuItemContainer()
{
    for (unsigned int i=0;i<allItems.size();i++)
        delete allItems[i];
}

bool CModuleMenuItemContainer::setItemState(int commandID,bool checked,bool enabled,const char* newLabel)
{
    for (unsigned int i=0;i<allItems.size();i++)
    {
        if (allItems[i]->setItemState(commandID,checked,enabled,newLabel))
            return(true);
    }
    return(false);
}

bool CModuleMenuItemContainer::addMenuBarItem(const char* title,int subItemCount,std::vector<int>& commandIDs)
{
    commandIDs.clear();
    if (subItemCount+_nextSmallItemCommandID-1>ADDITIONAL_TOOL_MENU_ITEM_END_CMD)
        return(false); // Too many!!
    CModuleMenuItem* it=nullptr;
    for (int i=0;i<int(allItems.size());i++)
    {
        if ( (allItems[i]->getMenuBarLabel()==title)&&(strlen(title)!=0) )
        {
            it=allItems[i];
            break;
        }
    }
    if (it==nullptr)
    { // That menu doesn't yet exist! We create it
        it=new CModuleMenuItem(title);
        allItems.push_back(it);
    }
    for (int i=0;i<subItemCount;i++)
    {
        commandIDs.push_back(_nextSmallItemCommandID);
        it->addItem(_nextSmallItemCommandID++);
    }
    return(true);
}

bool CModuleMenuItemContainer::addMenus(VMenu* myMenu)
{
    // From Qt this is only called if the custom menu was clicked (unlike in Windows)
    for (unsigned int i=0;i<allItems.size();i++)
        allItems[i]->addMenus(myMenu);
    if (allItems.size()>0)
        myMenu->appendMenuSeparator();
    App::worldContainer->addOnScriptContainer->addMenu(myMenu);
    return(true);
}

bool CModuleMenuItemContainer::processCommand(int commandID)
{ // Return value is true if the command belonged to object edition menu and was executed
    for (unsigned int i=0;i<allItems.size();i++)
    {
        if (allItems[i]->processCommand(commandID))
            return(true);
    }
    return(App::worldContainer->addOnScriptContainer->processCommand(commandID));
}
