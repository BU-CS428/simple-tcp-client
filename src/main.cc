/*
 * CS 528 - Computer Networks
 *
 * School of Computing, Binghamton University.
 *
 * authors: Gregory Maldonado
 * email  : gmaldonado@cs.binghamton.edu
 * date   : 05-29-2025
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <memory>
#include <netinet/in.h>
#include <spdlog/spdlog.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define HOST "127.0.0.1"
#define PORT 8080

int main()
{
    int sock{0};
    struct sockaddr_in serv_addr{};

    // Creating socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        SPDLOG_ERROR("Failed to create socket");
        return EXIT_FAILURE;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    SPDLOG_INFO("Attempting to connect to {}:{} ...", HOST, PORT);
    if (inet_pton(AF_INET, HOST, &serv_addr.sin_addr) <= 0)
    {
        SPDLOG_ERROR("Invalid address / Address not supported");
        return EXIT_FAILURE;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        SPDLOG_ERROR("Connection Failed: {}", strerror(errno));
        return EXIT_FAILURE;
    }

    std::string msg{"Hello from client\n"};
    send(sock, msg.c_str(), msg.size(), 0);
    SPDLOG_INFO("Msg Sent [size {}]: {}", std::to_string(msg.size()), msg);

    close(sock);

    return EXIT_SUCCESS;
}