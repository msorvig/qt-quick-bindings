

public class QtQuick {
  static {
      System.loadLibrary("qmlbindings_java");
  }

  public static void test() {
      System.out.println("Hello, World");  
  }

  public static void testString(String string) {
      System.out.println(string);  
  }

  public static void testStringList(String strings[]) {
      System.out.println(strings);  
  }

  public static int main(String argv[], String mainQmlFilePath) {
      return m_qmlbindings.qtMain(argv.length, argv, mainQmlFilePath);
  }

  public static int mainSimple(String mainQmlFilePath) {
      return m_qmlbindings.qtMainSimple(mainQmlFilePath);
  }


private static qmlbindings m_qmlbindings;
}