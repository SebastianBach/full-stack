import marimo
import text_conversion

__generated_with = "0.1.5"
app = marimo.App()


@app.cell
def __():
    import marimo as mo
    return mo,


@app.cell
def __(mo):
    mo.md("# Title Case Demonstration").left()
    return

@app.cell
def __(mo):
    date = text_conversion.get_library_build_date()
    mo.md(f"Library Build date: {date}").left()
    return

@app.cell
def __(mo):
    text = mo.ui.text(placeholder="Enter text ...", label="Headline:", full_width=True)
    return text,


@app.cell
def __(mo, text):
    import text_conversion
    result = text_conversion.title_case(text.value)  
    return result


@app.cell
def __(mo, text, result):
    mo.vstack([text, mo.md(f"Result: \"{result}\"")])
    return


if __name__ == "__main__":
    app.run()