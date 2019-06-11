import java.util.HashMap;
import java.util.Map;

public class Ricettario {
	private static final Map<String, Integer> mappaCalorie;
	
	static {
		mappaCalorie = new HashMap<String, Integer>();
		mappaCalorie.put("funghi", 22);
		mappaCalorie.put("pistacchio", 562);
	    mappaCalorie.put("panna", 192);
	    mappaCalorie.put("wurstel", 230);
	    mappaCalorie.put("pasta", 131);
	    mappaCalorie.put("riso", 130);
	    mappaCalorie.put("cioccolato", 546);
	    mappaCalorie.put("salsa", 29);
	    mappaCalorie.put("pane", 265);
	    mappaCalorie.put("prosciutto cotto", 138);
	    mappaCalorie.put("uova", 155);
	    mappaCalorie.put("pancetta", 458);
	    mappaCalorie.put("pomodoro", 18);
	    mappaCalorie.put("sale", 0);
	    mappaCalorie.put("zucchero", 389);
	    mappaCalorie.put("mozzarella", 280);
	    mappaCalorie.put("pepe", 251);
	    mappaCalorie.put("tonno", 130);
	    mappaCalorie.put("salmone affumicato", 117);
	    mappaCalorie.put("patate", 77);
	    mappaCalorie.put("carne", 143);
	}
	
	static Pietanza getIngrediente(String ingrediente, int quantita) {
		return new Ingrediente(ingrediente, quantita, mappaCalorie.get(ingrediente));
	}
	
	static Pietanza getPreparato(String nomeRicetta) {
		return new Preparato(nomeRicetta);
	}
}
