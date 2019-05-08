import java.util.*;

public class Edificio { //Subject
	private List<Spia> spie;
	
	public Edificio() {
		spie = new ArrayList<>();
	}
	
	public void inviaSpia(Spia spia) { //attach()
		if(!spie.contains(spia))
			spie.add(spia);
	}
	
	public void ritiraSpia(Spia spia) { //detach()
		if(spie.contains(spia))
			spie.remove(spia);
	}
	
	public void avvertiSpia() { //notify()
		for(Spia spia: spie) {
			spia.eroeEntrato();
		}	
	}
}
