
public class ConcreteMediator implements Mediator {
	
	Visualizer v;
	Counter c;
	Adder a;
	Loader l;
	
	public ConcreteMediator() {
		this.v = new Visualizer();
		this.c = new Counter(this);
		this.a = new Adder(this);
		this.l = new Loader(this);
	}

	@Override
	public void taskCompleted(String task) {
		switch(task) {
			case "load" : {
				c.conta(l.getValues());
				a.adda(l.getValues());
			}
			case "sum" : {
				v.setSum(a.getSum());
			}
			case "count" : {
				v.setCount(c.getCount());
			}
		}

	}

	@Override
	public void loadValues() {
		l.loadValues();
	}

	@Override
	public void show() {
		v.show();
	}

}
