namespace WEB_253502_Lishykk.UI.Middleware
{
    public class LoggingMiddleware
    {
        private readonly RequestDelegate _next;
        private readonly ILogger<LoggingMiddleware> _logger;

        public LoggingMiddleware(RequestDelegate next, ILogger<LoggingMiddleware> logger)
        {
            _next = next;
            _logger = logger;
        }

        public async Task InvokeAsync(HttpContext context)
        {
            await _next(context); // Передаем запрос дальше по конвейеру

            if (context.Response.StatusCode < 200 || context.Response.StatusCode >= 300)
            {
                // Логируем запрос с кодом состояния не 2XX
                var logMessage = $"Request {context.Request.Path} returns {context.Response.StatusCode}";
                _logger.LogInformation(logMessage);
            }
        }
    }
}
