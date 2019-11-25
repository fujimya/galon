package com.example.sisca;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.NotificationCompat;
import androidx.core.app.NotificationManagerCompat;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        // Write a message to the database
        FirebaseDatabase database = FirebaseDatabase.getInstance();
        DatabaseReference myRef = database.getReference("galon/level");

        // Read from the database
        myRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                // This method is called once with the initial value and again
                // whenever data at this location is updated.
                String value = dataSnapshot.getValue(String.class);
                Log.d("Perubahan", "Value is: " + Double.parseDouble(value));
                TextView level = findViewById(R.id.level);
                Double lev = (100 - ((Double.parseDouble(value) / 24) * 100));
                level.setText(String.format("%.2f",lev)+" %");

                if(lev < 20){
                    Toast.makeText(MainActivity.this, "Level air minim, silahkan diisi",Toast.LENGTH_LONG).show();
                    NotificationCompat.Builder builder = new NotificationCompat.Builder(MainActivity.this)
                            .setSmallIcon(R.drawable.ic_launcher_background)
                            .setContentTitle("Galon Air")
                            .setContentText("Silahkan isi lagi galom airnya")
                            .setPriority(NotificationCompat.PRIORITY_DEFAULT);

                    NotificationManagerCompat notificationManager = NotificationManagerCompat.from(MainActivity.this);

// notificationId is a unique int for each notification that you must define
                    notificationManager.notify(1, builder.build());
                }
            }

            @Override
            public void onCancelled(DatabaseError error) {
                // Failed to read value
                Log.w("Gagal", "Failed to read value.", error.toException());
            }
        });
    }
}
