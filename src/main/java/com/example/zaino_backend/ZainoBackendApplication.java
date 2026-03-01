package com.example.zaino_backend;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.*;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

@SpringBootApplication  // Avvisa Java che questo programma � un Server WEB
@RestController  // Quello che restituiscono i metodi di java vengono inviati al Browser come dati puri
@CrossOrigin // Questo ci permette di accettare dati da chiunque
@RequestMapping("/api")  // Tutte le richieste verso questo server inizieranno con http://localhost:8080/api

public class ZainoBackendApplication {
    // Questo risponde al browser (richiesta GET)
    @GetMapping
    public String salutoDalBrowser() {
        return "Benvenuto nel Server dello Zaino! Il motore C e' pronto a calcolare. Usa una richiesta POST su /api/ottimizza per inviare i dati.";
    }

    public static void main(String[] args) {
	SpringApplication.run(ZainoBackendApplication.class, args);  // Facciamo partire Spring Boot
    }

    @PostMapping("/ottimizza")  // Se qualcuno manda i dati all'indirizzo /api/ottimizza, Spring Boot eseguir� qeusta funzione
    public String calcolaItinerario(@RequestBody RichiestaViaggio req){
	StringBuilder risultato = new StringBuilder();
	try{
	    List<String> comando = new ArrayList<>();
	    comando.add("zaino.exe");
	    comando.add(String.valueOf(req.capacita));
	    comando.add(String.valueOf(req.valori.length));

	    for(int v : req.valori) comando.add(String.valueOf(v));
	    for(int w : req.pesi) comando.add(String.valueOf(w));

	    ProcessBuilder pb = new ProcessBuilder(comando);
	    Process processo = pb.start();

	    BufferedReader reader= new BufferedReader(new InputStreamReader(processo.getInputStream()));
	    String linea;
	    while((linea = reader.readLine()) != null){
		risultato.append(linea).append("\n");
	    }
	    processo.waitFor();
	}catch(Exception e){
	    return "Errore del server: " + e.getMessage();
	}
	return risultato.toString();
    }
}
/* Classe per prendere la richiesta del viaggio */
class RichiestaViaggio{
    public int capacita;
    public int[] valori;
    public int[] pesi;
}
