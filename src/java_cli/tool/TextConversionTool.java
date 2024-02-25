public class TextConversionTool {

    public static void main(String[] args) {

        if (args.length < 1) {
            System.out.println("Missing command line argument.");
            System.exit(1);
            return;
        }

        TextConversion conversion = new TextConversion();

        String input = args[0];
        System.out.println("Input: " + input);

        String result = conversion.titleCase(input);

        System.out.println("Output: " + result);

        System.exit(0);
    }
}
