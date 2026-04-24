import java.io.*; 
import java.net.*;

class ClientThreadREST {
    public static void main(String args[])
    {
        if(args.length < 3)    {
            System.out.println("USAGE: java ClientREST tipofunzione op1 op2");
        }   
        else  {

            if (args[0].equals("calcola-somma")) {
                RESTAPI service = new RESTAPI("127.0.0.1", 8000, args[0], args[1], args[2]);
                service.start();
            }
            else if (args[0].equals("numeri-primi")) {
                int min = Integer.parseInt(args[1]);
                int max = Integer.parseInt(args[2]);
                int range = max - min;

                if (range < 100000) {
                    RESTAPI service = new RESTAPI("127.0.0.1", 8000, args[0], args[1], args[2]);
                    service.start();    
                }
                else {
                    int step = range / 3;

                    // Calcolo i tre intervalli
                    String min1 = String.valueOf(min);
                    String max1 = String.valueOf(min + step);

                    String min2 = String.valueOf(min + step + 1);
                    String max2 = String.valueOf(min + 2 * step);

                    String min3 = String.valueOf(min + 2 * step + 1);
                    String max3 = String.valueOf(max); // L'ultimo arriva fino al max originale

                    // Assegno i range specifici a ogni server
                    RESTAPI service1 = new RESTAPI("127.0.0.1", 8000, args[0], min1, max1);
                    RESTAPI service2 = new RESTAPI("127.0.0.1", 8001, args[0], min2, max2);
                    RESTAPI service3 = new RESTAPI("127.0.0.1", 8002, args[0], min3, max3);
                    
                    service1.start();
                    service2.start();
                    service3.start();
                }
            }
        }
    }
}

class RESTAPI extends Thread
{
    String server, service, param1, param2;
    int serverPort;

    public void run()   {
        if(service.equals("calcola-somma")) {
            calcolaSomma(Float.parseFloat(param1), Float.parseFloat(param2));
        }
        else if (service.equals("numeri-primi")) {
            numeriPrimi(Integer.parseInt(param1), Integer.parseInt(param2));
        }
        else {
            System.out.println("Servizio non disponibile!");
        }
    }

    RESTAPI(String remoteServer, int portIn, String srvc, String p1, String p2)  {
        server = new String(remoteServer);
        serverPort = portIn;
        service = new String(srvc);
        param1 = new String(p1);
        param2 = new String(p2);
    }

    synchronized void calcolaSomma(float val1, float val2)  {
        URL u = null;

        try { 
            u = URI.create("http://" + server + ":" + serverPort + "/calcola-somma?param1=" + val1 + "&param2=" + val2).toURL();
            System.out.println("URL aperto: " + u);
            conn(u);
        }
        catch (MalformedURLException e) {
            System.out.println("URL errato: " + u);
        }
    }

    synchronized void numeriPrimi(int min, int max) {
        URL u = null;

        try { 
            u = URI.create("http://" + server + ":" + serverPort + "/numeri-primi?min=" + min + "&max=" + max).toURL();
            System.out.println("URL aperto: " + u);
            conn(u);
        }
        catch (MalformedURLException e) {
            System.out.println("URL errato: " + u);
        }
    }

    synchronized void conn(URL u) {
        try {
            URLConnection c = u.openConnection();
            c.connect();
            BufferedReader b = new BufferedReader(new InputStreamReader(c.getInputStream()));
            System.out.println("Lettura dei dati...");
            String s;
            while( (s = b.readLine()) != null ) {
                System.out.println(s);
            }
        }
        catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
