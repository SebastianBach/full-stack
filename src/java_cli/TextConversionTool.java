public class TextConversionTool {

     static {
        System.loadLibrary("java_text_conversion");
    }

    public native void textConversionC(byte[] buf, int size);

    public static void main(String[] args) {

        if (args.length < 1) {
            System.out.println("Missing command line argument.");
            return;
        }

        TextConversionTool tool = new TextConversionTool();

        String input = args[0];
        System.out.println("Input: " + input);

        byte[] data = input.getBytes();
        tool.textConversionC(data, data.length);

        String result = new String(data);

        System.out.println("Output: " + result);
    }
}
