/**
 *
 * @author sey
 *
 * @version $Id: $
 *
 */
public class HelloWorldJNI {
    static {
        // ライブラリをロードします
        System.loadLibrary("HelloWorldJNI");
    }

    // ネイティブメソッドを宣言します
    public native String sayHelloWorld();

    public static void main(String[] args) {
        HelloWorldJNI hello = new HelloWorldJNI();
        // メソッドを実行して表示します
        System.out.println(hello.sayHelloWorld());
    }
}
