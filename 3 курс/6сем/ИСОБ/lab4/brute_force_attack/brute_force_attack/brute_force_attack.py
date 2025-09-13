import asyncio
import aiohttp
import ssl

async def brute_force_attack(target_url, num_requests):
    ssl_context = ssl.create_default_context()
    ssl_context.check_hostname = False
    ssl_context.verify_mode = ssl.CERT_NONE

    for i in range(num_requests):
        try:
            async with aiohttp.ClientSession() as session:  # Создаем новую сессию для каждого запроса
                async with session.get(target_url, ssl=ssl_context) as response:
                    print(f"Request {i+1}: {response.status}")
        except aiohttp.ClientError as e:
            print(f"Request {i+1} failed: {e}")
        except ssl.SSLError as e:
            print(f"SSL error on request {i+1}: {e}")

        await asyncio.sleep(0.05)  # Уменьшенная задержка между запросами

target_url = 'https://127.0.0.1:8080/'

asyncio.run(brute_force_attack(target_url, 1000))
