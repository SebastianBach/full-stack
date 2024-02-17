public class UnitTest {

    static {
        System.loadLibrary("java_text_conversion");
    }

    public static void main(String[] args) {

        TextConversion conversion = new TextConversion();

        String input = "this is a headline";

        String result = conversion.titleCase(input);

        System.out.println(result);

        String expected = "This Is a Headline";

        if (!result.equals(expected))
            System.exit(1);

        System.exit(0);
    }
}
