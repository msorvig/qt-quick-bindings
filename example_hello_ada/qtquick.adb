with Interfaces.C.Strings; use Interfaces.C.Strings;

package body QtQuick is
    procedure Qt_Main (MainQmlFile : String) is
    begin
        Qt_Main_Simple(New_String(MainQmlFile));
    end Qt_Main;
end QtQuick;
