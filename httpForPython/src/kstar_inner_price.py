# -*- coding:utf-8 -*-
import os
import sys
import time
import pytz
from urllib import parse
from http.server import BaseHTTPRequestHandler

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../../')))

import arrow

from kuaishoustar_video.handler.handler_es.kuaistar.video import EsUserVideo


class ReadIn(object):
    tz = pytz.timezone('Asia/Shanghai')

    @classmethod
    def read_in_data(cls, docs):
        for elem in list(EsUserVideo.bulk_upsert(docs)):
            if not elem[0]:
                print(elem)
                return False
        return True

    @classmethod
    def create_time(cls):
        return str(arrow.get(time.time()).to(tz=cls.tz))


class GetHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        parsed_path = parse.urlparse(self.path)
        user_id = None
        price = None
        for elem in parsed_path.query.split('&'):
            if "user_id" in elem:
                user_id = elem.split("=")[-1]
            elif "price" in elem:
                price = elem.split("=")[-1]
        if user_id is None or price is None:
            message = "传入参数有误: user_id or price is Null"
            self.send_response(200)
            self.send_header('Content-Type',
                             'text/plain; charset=utf-8')
            self.end_headers()
            self.wfile.write(message.encode('utf-8'))
        else:
            doc = [{
                "user_id": int(user_id),
                "order_Bid": int(price),
                "one_day_price": int(price),
                "three_days_price": int(price),
                "seven_days_price": int(price),
                "timestamp": ReadIn.create_time(),
            }]
            if ReadIn.read_in_data(doc):
                message = "{" + f"{user_id}: \"Success, Waiting for the ElasticSearch flash\"" + "}"
                self.send_response(200)
                self.send_header('Content-Type',
                                 'text/plain; charset=utf-8')
                self.end_headers()
                self.wfile.write(message.encode('utf-8'))
            else:
                message = "\"ElasticSearch ERROR\""
                self.send_response(200)
                self.send_header('Content-Type',
                                 'text/plain; charset=utf-8')
                self.end_headers()
                self.wfile.write(message.encode('utf-8'))


if __name__ == '__main__':
    # nohup /alidata/server/imfaker/.venv/bin/python /partita/kuaishoustar_video/task/kstar_inner_price.py > kstar_inner_price.log 2>&1&
    # http://10.0.13.105:9002/kstar_inner?user_id=776855335&price=1000000
    from http.server import HTTPServer

    server = HTTPServer(('10.0.13.105', 9002), GetHandler)
    # server = HTTPServer(('127.0.0.1', 8001), GetHandler)
    print('Starting server, use <Ctrl-C> to stop')
    server.serve_forever()
