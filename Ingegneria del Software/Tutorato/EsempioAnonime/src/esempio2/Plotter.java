package esempio2;

import java.util.List;

public class Plotter {
	List<Double> list;
	
	Plotter(List<Double> list){
		this.list = list;
	}
	
	public void plot(Function f) {
		System.out.println("x\tf(x)\n");
		for(Double d : list)
			System.out.format("%.1f\t%.2f\n", d, f.calculate(d));
		System.out.println("----------------------");
	}
}
