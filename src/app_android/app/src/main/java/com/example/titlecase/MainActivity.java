package com.example.titlecase;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;
import android.view.View;


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


                binding.editText.setText(editFromJNI(text));
            }
        });
    }
    
    public native String stringFromJNI();
    public native String editFromJNI(String input);
}