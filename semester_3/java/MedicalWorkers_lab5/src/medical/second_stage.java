package medical;

import java.io.*;
import java.text.DateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.NoSuchElementException;
import java.util.ResourceBundle;

abstract class MedicalWorker implements Serializable {
	private static final long serialVersionUID = 1L;
	public static int count = 0;

	private String name;
	private Date creationTime;
	private transient String info = "";

	protected MedicalWorker(String name) {
		if (name == null || name.trim().isEmpty()) {
			throw new IllegalArgumentException("error.invalid_name");
		}
		this.name = name;
		this.creationTime = new Date();
		count++;
	}

	public String getName() { return name; }
	public Date getCreationTime() { return creationTime; }
	public String getInfo() { return info; }
	public void setInfo(String info) { this.info = info; }

	public String getLocalizedRole(ResourceBundle bundle) {
		String key = "role." + getClass().getSimpleName();
		try {
			return bundle.getString(key);
		} catch (Exception e) {
			return getClass().getSimpleName();
		}
	}

	@Override
	public String toString() {
		return getClass().getSimpleName() + ": " + name;
	}
}

class Nurse extends MedicalWorker {
	private static final long serialVersionUID = 1L;
	public Nurse(String name) { super(name); }
}

class Feldsher extends MedicalWorker {
	private static final long serialVersionUID = 1L;
	public Feldsher(String name) { super(name); }
}

abstract class Doctor extends MedicalWorker {
	private static final long serialVersionUID = 1L;
	protected Doctor(String name) { super(name); }
}

class Therapist extends Doctor {
	private static final long serialVersionUID = 1L;
	public Therapist(String name) { super(name); }
}

class Cardiologist extends Doctor {
	private static final long serialVersionUID = 1L;
	public Cardiologist(String name) { super(name); }
}

class Surgeon extends Doctor {
	private static final long serialVersionUID = 1L;
	public Surgeon(String name) { super(name); }
}

class Team implements Serializable {
	private static final long serialVersionUID = 1L;

	private Doctor doctor;
	private MedicalWorker helper;
	private Date creationTime;

	public Team(Doctor doctor, MedicalWorker helper) {
		if (doctor == null) {
			throw new IllegalArgumentException("error.no_doctor");
		}
		if (!(helper instanceof Nurse || helper instanceof Feldsher)) {
			throw new IllegalArgumentException("error.no_helper");
		}
		this.doctor = doctor;
		this.helper = helper;
		this.creationTime = new Date();
	}

	public Doctor getDoctor() { return doctor; }
	public MedicalWorker getHelper() { return helper; }
	public Date getCreationTime() { return creationTime; }

	public String toStringLocalized(ResourceBundle bundle) {
		String docRole = doctor.getLocalizedRole(bundle);
		String helpRole = helper.getLocalizedRole(bundle);
		
		String createdLabel = bundle.getString("label.created");
		
		String dtStr = DateFormat.getDateTimeInstance(DateFormat.MEDIUM, DateFormat.MEDIUM, bundle.getLocale()).format(doctor.getCreationTime());
		String htStr = DateFormat.getDateTimeInstance(DateFormat.MEDIUM, DateFormat.MEDIUM, bundle.getLocale()).format(helper.getCreationTime());

		String docInfo = (doctor.getInfo() != null && !doctor.getInfo().isEmpty()) ? " info: " + doctor.getInfo() : "";
		String helpInfo = (helper.getInfo() != null && !helper.getInfo().isEmpty()) ? " info: " + helper.getInfo() : "";

		return docRole + ": " + doctor.getName() + " [" + createdLabel + ": " + dtStr + "]" + docInfo 
				+ " + " 
				+ helpRole + ": " + helper.getName() + " [" + createdLabel + ": " + htStr + "]" + helpInfo;
	}

	@Override
	public String toString() {
		return doctor + " + " + helper;
	}
}

class Connector {
	private File file;

	public Connector(String filename) {
		this.file = new File(filename);
	}

	public void write(Team[] teams) throws IOException {
		try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(file))) {
			oos.writeInt(teams.length);
			for (Team team : teams) {
				oos.writeObject(team);
			}
			oos.flush();
		}
	}

	public Team[] read() throws IOException, ClassNotFoundException {
		try (ObjectInputStream oin = new ObjectInputStream(new FileInputStream(file))) {
			int length = oin.readInt();
			Team[] result = new Team[length];
			for (int i = 0; i < length; i++) {
				result[i] = (Team) oin.readObject();
			}
			return result;
		}
	}

	public Team read(int index) throws IOException, ClassNotFoundException {
		Team[] all = read();
		if (index < 0 || index >= all.length) {
			throw new NoSuchElementException("error.file_not_found");
		}
		return all[index];
	}
}

public class second_stage {
	public static void main(String[] args) {
		Locale locale = Locale.getDefault();
		if (args.length >= 2) {
			locale = new Locale(args[0], args[1]);
		} else if (args.length == 1) {
			locale = new Locale(args[0]);
		}
		ResourceBundle bundle = ResourceBundle.getBundle("medical.Msg", locale);

		try {
			System.out.println("--- " + bundle.getString("info.app.start") + " ---");

			MedicalWorker nurse = new Nurse("Иванова");
			nurse.setInfo("ночная смена");
			MedicalWorker nurse2 = new Nurse("Сидорова");
			MedicalWorker feldsher = new Feldsher("Кузнецов");
			Doctor therapist = new Therapist("Петров");
			Doctor cardiologist = new Cardiologist("Смирнова");
			Doctor SurgeonDoc = new Surgeon("Волков");

			MedicalWorker[] workers = { nurse, nurse2, feldsher, therapist, cardiologist, SurgeonDoc };

			System.out.println(bundle.getString("info.workers.created"));

			Team[] teams = {
				new Team(therapist, nurse),
				new Team(cardiologist, feldsher),
				new Team(SurgeonDoc, nurse2)
			};

			System.out.println(bundle.getString("info.teams.formed"));

			Connector con = new Connector("teams_stage2.dat");
			con.write(teams);
			System.out.println(bundle.getString("info.file.saved"));
			
			Team[] readTeams = con.read();
			System.out.println(bundle.getString("info.file.read"));
			System.out.println();

			System.out.println(bundle.getString("teams.title"));
			for (Team t : readTeams) {
				System.out.println(t.toStringLocalized(bundle));
			}
			System.out.println();

			try {
				con.read(10);
			} catch (NoSuchElementException e) {
				System.err.println(bundle.getString(e.getMessage()));
			}

			System.out.println(bundle.getString("workers.count") + " " + MedicalWorker.count);
			System.out.println("--- " + bundle.getString("info.process.completed") + " ---");

		} catch (OutOfMemoryError e) {
			System.err.println(bundle.getString("error.oom"));
		} catch (Exception e) {
			String messageKey = e.getMessage();
			try {
				System.err.println(bundle.getString(messageKey));
			} catch (Exception ex) {
				System.err.println(e.getMessage());
			}
		}
	}
}