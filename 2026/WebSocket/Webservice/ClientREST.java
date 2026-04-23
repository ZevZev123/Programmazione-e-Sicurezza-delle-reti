import java.io.*; 
import java.net.*;

class ClientREST 
{    
    public static void main(String args[])
    {
        RESTAPI service1 = new RESTAPI("127.0.0.1");

        if(args.length < 3)    {
            System.out.println("USAGE: java ClientREST tipofunzione op1 op2");
        }   
        else if(args[0].equals("calcola-somma")) {
            service1.calcolaSomma(Float.parseFloat(args[1]), Float.parseFloat(args[2]));
        }
        else if(args[0].equals("numeri-primi")) {
            service1.numeriPrimi(Integer.parseInt(args[1]), Integer.parseInt(args[2]));
        }
    }
}

class RESTAPI
{
    String server;

    RESTAPI(String remoteServer)  {
        server = new String(remoteServer);
    }

    void calcolaSomma(float val1, float val2)  {
        URL u = null;

        try { 
            u = URI.create("http://" + server + ":8000/calcola-somma?param1=" + val1 + "&param2=" + val2).toURL();       // per evitare il warning con java 20+
            // u = new URL("http://"+server+":8000/calcola-somma?param1="+val1+"&param2="+val2);
            System.out.println("URL aperto: " + u);
            conn(u);
        }
        catch (MalformedURLException e) {
            System.out.println("URL errato: " + u);
        }
    }    

    void numeriPrimi(int min, int max) {
        URL u = null;

        try { 
            u = URI.create("http://" + server + ":8000/numeri-primi?min=" + min + "&max=" + max).toURL();       // per evitare il warning con java 20+
            // u = new URL("http://"+server+":8000/numeri-primi?min="+min+"&max="+max);
            System.out.println("URL aperto: " + u);
            conn(u);
        }
        catch (MalformedURLException e) {
            System.out.println("URL errato: " + u);
        }
    }

    void conn(URL u) {
        try {
            URLConnection c = u.openConnection();
            c.connect();
            BufferedReader b = new BufferedReader(new InputStreamReader(c.getInputStream()));
            System.out.println("Lettura dei dati...");
            String s;
            while( (s = b.readLine()) != null ) {
                // legge riga per riga il messaggio di ritorno dal server
                System.out.println(s);
            }
        }
        catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
