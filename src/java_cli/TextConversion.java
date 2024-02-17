public class TextConversion {

    static {
        System.loadLibrary("java_text_conversion");
    }

    private native void textConversionC(byte[] buf, int size);

    public String titleCase(String input) {

        byte[] data = input.getBytes();

        textConversionC(data, data.length);

        return new String(data);
    }
}
