#ifndef BOT_NET_NRF24L01_H
#define BOT_NET_NRF24L01_H

#include "net.h"

namespace gdcl {

namespace net {

struct nrf24l01 : radio {
	int pull() override;
	int push() override;
};

} // namespace net

} // namespace gdcl

#endif
