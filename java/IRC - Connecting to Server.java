// Daily Programmer 3-14-16 : https://www.reddit.com/r/dailyprogrammer/comments/4ad23z/20160314_challenge_258_easy_irc_making_a/
// IRC - Making a Connection
// Author: Ken Figueiredo

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class Mar14 {
	
	public static class ircClient{
		private Socket socket;
		private BufferedReader in;
		private PrintWriter out;
		private String host, name, user;
		private int portNum;
		
			public ircClient(String[] args){
				String[] t = args[0].split(":");			
				host = t[0];
				portNum = Integer.parseInt(t[1]);
				name = "NICK " + args[1];
				user = "USER " + args[2] + " 0 * :" + args[3] + " " + args[4];
			}
			
			/** openConnection()
			 * Attempts to open connection from given params
			 * Returns true if connection is successful
			 * Returns false otherwise
			 */
			private boolean openConnection(){
				try {
					socket = new Socket(this.host, this.portNum);
					in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
					out = new PrintWriter(socket.getOutputStream(),true);
				} catch (UnknownHostException e) {
					System.err.println("Unknown host: " + this.host + ":" + this.portNum);
					return false;
				} catch (IOException e) {
					System.err.println("I/O error: " + e.toString());
					return false;
				}				
				return true;
			}
			
			/** sendCredentials()
			 * Sends the crendentials of the user to the server
			 */
			private void sendCredentials(){
				out.println(this.name);
				out.println(this.user);				
			}
			
			/** getServerMsg()
			 * Attempts to get a message from the server
			 * and returns it.
			 */
			private String getServerMsg() throws IOException{
				return in.readLine();
			}
			
			/** sendMsg(String msg)
			 * Takes the given string and passes it to the server.
			 */
			private void sendMsg(String msg){
				System.out.println("> " + msg);
				out.println(msg);			
			}
			
			/** replyPong(String ping)
			 * Takes the given string, which should be the server Ping
			 * and returns a Pong message to the server
			 */
			private void replyPong(String ping){
				String[] msg = ping.split(":");
				sendMsg("PONG :" + msg[1]);
			}
			
			/** closeConnect()
			 * Attempts to close the connection to the server
			 * Returns true if the connection is closed successfully
			 * Returns false otherwise
			 */
			private boolean closeConnection(){
				try {
					socket.close();
					out.close();
					in.close();
				} catch (IOException e) {
					System.err.println("I/O error: " + e.toString());
					return false;
				}
				
				return true;
			}
	}
	
	public static void main(String[] args) throws IOException {
		
		ircClient irc = new ircClient(args);
			irc.openConnection();
			irc.sendCredentials();
			
			String serverMsg;
			while((serverMsg = irc.getServerMsg()) != null){
				System.out.println(serverMsg);
				
				if(serverMsg.contains("PING")){					
					irc.replyPong(serverMsg);
				}
			}			
		irc.closeConnection();
	}
}
