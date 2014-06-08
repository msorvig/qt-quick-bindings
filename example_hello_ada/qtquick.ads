with Interfaces.C.Strings; use Interfaces.C.Strings;

package QtQuick is
    -- public idiomatic Ada API
    procedure Qt_Main (MainQmlFile : String);
private
    -- Imported C API
    procedure Qt_Main_Simple (MainQmlFile : chars_ptr);
    pragma Import (C, Qt_Main_Simple, "qtMainSimple");
end QtQuick;
