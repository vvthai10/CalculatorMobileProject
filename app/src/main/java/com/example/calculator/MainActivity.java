package com.example.calculator;

import static android.widget.GridLayout.spec;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.widget.Button;
import android.widget.GridLayout;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.util.Objects;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private int nextAvailableId = 65000;


    private String val1 = "";
    private String val2 = "";
    private String op = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Thêm linear_layout 6 nút trên một hàng - chưa thêm xử lý cho phần này vì chưa hiểu quy cách hoạt động
        AddLayoutMemory();

        // Thêm một grid_layout cho 24 nút gồm 6 x 4
        AddLayoutNumerals();

    }

    private void AddLayoutMemory(){
        LinearLayout layout = (LinearLayout)findViewById(R.id.wrapper);
        layout.addView(getLayoutMemory());
    }

    public LinearLayout getLayoutMemory() {
        String[] listMemory = {"MC", "MR", "M+", "M-", "MS", "Mv"};
        LinearLayout linearM = new LinearLayout(this);
        linearM.setOrientation(LinearLayout.HORIZONTAL);
        linearM.setWeightSum(6);

        // Set default weight for all btn
        LinearLayout.LayoutParams paramsBtn = new LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        paramsBtn.weight = 1.0f;

        for(int i = 0; i < 6; i++){
            Button btn = new Button(this);
            btn.setText(listMemory[i]);
            btn.setLayoutParams(paramsBtn);
            btn.setHeight(50);
            btn.setId(nextAvailableId++);
            linearM.addView(btn);
        }

        return linearM;
    }


    private void AddLayoutNumerals() {
        LinearLayout layout = findViewById(R.id.wrapper);
        layout.addView(getLayoutNumerals());
    }

    private GridLayout getLayoutNumerals() {
        String[] listNumerals = {"%", "CE", "C", "<=",
                                "1/x", "x^2", "sqrt(x)", "/",
                                "7", "8", "9", "*",
                                "4", "5", "6", "-",
                                "1", "2", "3", "+",
                                "+/-", "0", ".", "=",};
        GridLayout layoutNum = new GridLayout(this);

        int total = 24;
        int column = 4;
        int row = total / column;
        layoutNum.setColumnCount(column);
        layoutNum.setRowCount(row + 1);
        for(int i =0, c = 0, r = 0; i < total; i++, c++)
        {
            if(c == column)
            {
                c = 0;
                r++;
            }
            Button btn = new Button(this);
            btn.setText(listNumerals[i]);
            btn.setHeight(50);
            btn.setId(nextAvailableId++);

            GridLayout.LayoutParams param =new GridLayout.LayoutParams();
            param.height = GridLayout.LayoutParams.WRAP_CONTENT;
            param.width = GridLayout.LayoutParams.WRAP_CONTENT;
            param.topMargin = 5;
            param.rightMargin = 10;
            param.setGravity(Gravity.CENTER);
            param.columnSpec = GridLayout.spec(c);
            param.rowSpec = GridLayout.spec(r);

            if(i == total - 1){
                btn.setBackgroundColor(Color.rgb(100,200,255));
            }
            btn.setOnClickListener(this);
            btn.setLayoutParams (param);
            layoutNum.addView(btn);
        }
        return layoutNum;
    }

    @Override
    public void onClick(View v){
        try {
            // Get 2 text view:
            TextView viewInput = findViewById(R.id.screen_in_out_calc);
            TextView viewCalc = findViewById(R.id.screen_calc);

            Button btn = (Button)v;
            String target = btn.getText().toString();

            switch (target){
                case "%": case "CE": case "C": case "<=": case"1/x": case"x^2": case "sqrt(x)": case"+/-": case ".":
                    Log.d("My note: ", "Features is updating...");
                // Thực hiện ghi thông số đang nhập
                case "+": case"-": case"*": case"/":
                    if(op == ""){
                        op = target;
                    }
                    else{
                        if(op == "+"){
                            val1 = String.valueOf(Double.valueOf(val1) + Double.valueOf(val2));
                        }
                        else if(op == "-"){
                            val1 = String.valueOf(Double.valueOf(val1) - Double.valueOf(val2));
                        }
                        else if(op == "*"){
                            val1 = String.valueOf(Double.valueOf(val1) * Double.valueOf(val2));
                        }
                        else if(op == "/"){
                            val1 = String.valueOf(Double.valueOf(val1) / Double.valueOf(val2));
                        }
                        op = target;
                        val2 = "";
                    }
                    break;
                // Thực hiện tính toán
                case "=":
                    Log.d("My info", "handle =");
                    Log.d("My info operation: ", val1 + val2 + op);
                    if(!Objects.equals(val1, "") && !Objects.equals(val2, "") && !Objects.equals(op, "")){
                        if(op == "+"){
                            val1 = String.valueOf(Double.valueOf(val1) + Double.valueOf(val2));
                        }
                        else if(op == "-"){
                            val1 = String.valueOf(Double.valueOf(val1) - Double.valueOf(val2));
                        }
                        else if(op == "*"){
                            val1 = String.valueOf(Double.valueOf(val1) * Double.valueOf(val2));
                        }
                        else if(op == "/"){
                            val1 = String.valueOf(Double.valueOf(val1) / Double.valueOf(val2));
                        }
                        op = "";
                        val2 = "";
                    }
                    break;
                // Thực hiện nhập các số
                default:
                    // Nếu chưa nhập phép toán
                    if(op == ""){
                        val1 = val1 + target;
                        Log.d("My info: ", val1);
                        viewInput.setText(val1);
                    }
                    else{
                        val2 += target;
                        viewInput.setText(val2);
                    }
                    break;
            }

            if(op != "" || target == "="){
                viewCalc.setText(val1 + " " + op + " " + val2);
            }
        }
        catch(Exception e){
            Log.e("My error:", e.toString());
        }
    }

}

