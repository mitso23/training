#include <gio/gio.h>
#include <stdlib.h>
#include <iostream>
#include <fcntl.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int
main (int argc, char *argv[])
{
	char * mysocketpath = "/tmp/skata";
	struct sockaddr_un namesock;
	int fd;
	namesock.sun_family = AF_UNIX;
	strncpy(namesock.sun_path, (char *) mysocketpath, sizeof(namesock.sun_path));
	fd = socket(AF_UNIX, SOCK_DGRAM, 0);
	GError* error = NULL;

	auto guid = g_dbus_generate_guid();
	auto server_flags = G_DBUS_SERVER_FLAGS_NONE;

	auto server = g_dbus_server_new_sync("unix:path=/tmp/skata", server_flags,
			guid, NULL, 	/* GDBusAuthObserver */
			NULL, 			/* GCancellable */
			&error);

	g_dbus_server_start(server);

	if (error)
	{
		std::cout << "SKATA" << std::endl;
	}

	GDBusConnection *connection;
	const gchar *greeting_response;
	GVariant *value;
	gchar *greeting;

	error = NULL;
	connection = g_dbus_connection_new_for_address_sync("unix:path=/tmp/skata",
			G_DBUS_CONNECTION_FLAGS_NONE, NULL, /* GDBusAuthObserver */
			NULL, /* GCancellable */
			&error);

	if (connection == NULL)
	{
		std::cout << "SHIIIIT" << std::endl;
	}

	close(fd);
	unlink("/tmp/skata");

}

