package com.example.titlecase;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;
import android.view.View;

import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;

import com.example.titlecase.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'titlecase' library on application startup.
    static {
        System.loadLibrary("titlecase");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        binding.buttonConvert.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Update the TextView with the string from JNI
                String text = binding.editText.getText().toString();

                binding.editText.setText(titleCase(text));

            }
        });

        binding.buttonCopy.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ClipboardManager clipboard = (ClipboardManager) MainActivity.this.getSystemService(Context.CLIPBOARD_SERVICE);

                String text = binding.editText.getText().toString();
                ClipData clip = ClipData.newPlainText("label", text);

                clipboard.setPrimaryClip(clip);
            }
        });
    }

    /**
     * A native method that is implemented by the 'titlecase' native library,
     * which is packaged with this application.
     */
    public native String titleCase(String input);
}