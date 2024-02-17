public class TextConversion {

    static {
        try {
            System.loadLibrary("java_text_conversion");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Failed to load the java_text_conversion library: " + e.getMessage());
        }
    }

    /**
     * Intern.
     */
    private native void textConversionC(byte[] buf, int size);

    /**
     * Converts the input text string into title case.
     *
     * @param input The input string to be converted to title case.
     * @return A new string object representing the title-cased version of the input
     *         string.
     */
    public String titleCase(String input) {

        if (input == null || input.isEmpty()) {
            return new String("");
        }

        byte[] data = input.getBytes();

        textConversionC(data, data.length);

        return new String(data);
    }
}
